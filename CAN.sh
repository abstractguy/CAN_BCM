# CAN.sh
# Creator: Samuel Duclos
# Comments:
#     This file is directly invoked using source.
#     This prevents file descriptors from getting
#     closed prematurely with an exiting subshell.
# Documentation:
#     https://github.com/linux-can/can-utils/blob/master/bcmserver.c
# Example usage:
#     source /home/debian/labs/CAN/CAN.sh

# Modifiable variables.
INTERFACE_TYPE=vcan DELAY=1 DELAY_US=500000 DELAY_SEC=0

# Import libraries.
source libraries.sh

# Setup interface if it doesn't exist.
if [ ! -e "/sys/class/net/"$INTERFACE ]; then
    ip link add name $INTERFACE type $INTERFACE_TYPE
fi

# Making sure the interface is up.
ifconfig $INTERFACE up

# Starting CAN broadcast manager.
bcmserver &
PID_SERVER=$!

# Create character device for TCP/IP socket manipulation if it doesn't exist already.
if [ ! -e /dev/tcp ]; then
    mknod /dev/tcp c 30 36
fi

# Flush firewall rules to enable multiple binding of listeners to same socket.
iptables -F

# Waiting for server to boot.
sleep 1

# Linking socket to file descriptor to be used.
exec 3<>$SOCKET

# Redirecting file descriptor input to stdout.
cat <&3 &
PID_INPUT=$!

# Interruptions handled by kernel with callback functions.
trap safe_exit EXIT

# Send commands to server through file descriptor to socket:

# < INTERFACE ADD_CYCLE DELAY_SEC DELAY_US HEX_ADDRESS N_BYTES SPACE_SEPARATED_HEX_BYTES >
echo "<${INTERFACE} A ${DELAY_SEC} ${DELAY_US} 010 1 01>" >&3

# < INTERFACE RECEIVE_FROM DELAY_SEC DELAY_US HEX_ADDRESS N_BYTES FILTER >
echo "<${INTERFACE} R 0 0 010 1 FF>" >&3

while true :; do
    echo $SYNC
    # Test with 10 second timeout.
    read -t 10 SYNC
    if [[ "$?" > 128 ]]; then
        echo "SYNC timeout!"
        break
    elif [ "$SYNC" == 'ON' ]; then
        continue
    elif [ "$SYNC" == 'OFF' ]; then
        echo "Power down command received!"
        break
    else
        echo "Ill command received from computer."
        break
    fi
done

safe_exit
