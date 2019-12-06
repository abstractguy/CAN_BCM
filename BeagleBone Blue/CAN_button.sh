# Program:       CAN_button.sh
# Creator:       Samuel Duclos
# Comments:      This file is directly invoked using source.
#                This prevents file descriptors from getting
#                closed prematurely with an exiting subshell.
# Documentation: https://github.com/linux-can/can-utils/blob/master/bcmserver.c
# Example usage: sudo --prompt=temppwd su -c 'source /home/debian/CAN_button.sh' --preserve-environment

# Modifiable variables.
INTERFACE_TYPE=vcan
BITRATE=50000
DELAY_US=5000

# Non-modifiable variables.
INTERFACE=$INTERFACE_TYPE'0'
BITRATE='bitrate '$BITRATE
SOCKET=/dev/tcp/127.0.0.1/28600
GREEN_LED=/sys/class/leds/green
RED_LED=/sys/class/leds/red
GPIO=/sys/class/gpio
BUTTON=$GPIO'/gpio69/value'
BUTTON_STATE=1
MOTOR_STATE=0x00

# Set green and red LEDs to persistent mode.
echo 'none' > $GREEN_LED/trigger
echo 'none' > $RED_LED/trigger

# Turn green LED on and red LED off.
echo '255' > $GREEN_LED/brightness
echo '0' > $RED_LED/brightness

# Configure user button 2 (PAUSE_BTN, GPIO2_5).
echo 69 > $GPIO/export

if [ ! -e /dev/tcp ]
then
    # Create character device for TCP/IP socket manipulation if it doesn't exist already.
    mknod /dev/tcp c 30 36

    # Flush firewall rules to enable multiple binding of listeners to same socket.
    iptables -F
fi

# Virtual CAN interface has no bitrate.
if [ "$INTERFACE_TYPE" == 'vcan' ]
then
    BITRATE=
fi

# Setup interface if it doesn't exist.
if [ ! -e /sys/class/net/$INTERFACE ]
then
    ip link add dev $INTERFACE type $INTERFACE_TYPE $BITRATE
fi

# Making sure the interface is up.
ip link set up $INTERFACE

# Start CAN broadcast manager and wait for it to boot.
bcmserver &
PID_SERVER=$!
sleep 1

# Linking socket to file descriptor to be used.
exec {FILE_DESCRIPTOR}<>$SOCKET

function destroy {
    # Be nice and kill all nodes then wait.
    echo "<${INTERFACE} X 0 0 001 0 00>" >&$FILE_DESCRIPTOR # Delete receiver.
    sleep 1

    # Kill file descriptor.
    exec $FILE_DESCRIPTOR>&-

    # Kill server.
    kill $PID_SERVER

    # Destroy network interface.
    ip link set down $INTERFACE
    ip link delete dev $INTERFACE type $INTERFACE_TYPE

    # Configure user button 2 (PAUSE_BTN, GPIO2_5).
    echo 69 > $GPIO/unexport

    # Turn green LED off and red LED on.
    echo '0' > $GREEN_LED/brightness
    echo '255' > $RED_LED/brightness
}

# Let kernel trap shell exit interruptions.
trap destroy EXIT
trap destroy SIGTERM
trap destroy SIGINT
trap destroy SIGHUP

function time_precise {
    $(($(date +%s) * 1000000000 + $(date +%N)))
}

# Send commands to server through file descriptor to socket:

# < INTERFACE RECEIVE_FROM DELAY_SEC DELAY_US HEX_ADDRESS N_BYTES FILTER >
echo "<${INTERFACE} R 0 0 001 1 FF>" >&$FILE_DESCRIPTOR

# Main loop.
while true :
do
    # Read server output from file descriptor.
    read -t 0.001 -d '' -u $FILE_DESCRIPTOR CAN_INPUT

    if [ "$CAN_INPUT" == "< ${INTERFACE} R 0 0 001 1 01 >" ]
    then
        TIME=$(time_precise)
        while true:
        do
            if [ $(cat $BUTTON) == 1 ]
            then
                if [ "$BUTTON_STATE" == 0 ]
                then
                    BUTTON_STATE=1
                    if [ "$MOTOR_STATE" == 0x01 ]
                    then
                        MOTOR_STATE=0x00
                    else
                        MOTOR_STATE=0x01
                    fi
                fi
            else
                if [ "$BUTTON_STATE" == 1 ]
                then
                    BUTTON_STATE=0
                    if [ "$MOTOR_STATE" == 0x01 ]
                    then
                        MOTOR_STATE=0x00
                    else
                        MOTOR_STATE=0x01
                    fi
                fi
            fi

            if [[ $(($(time_precise) - $TIME)) > 3000000 ]]
            then
                break
            else
                continue
            fi
        done

        echo "<${INTERFACE} S 0 0 003 1 ${MOTOR_STATE}>" > &$FILE_DESCRIPTOR

    elif [ "$CAN_INPUT" == "< ${INTERFACE} R 0 0 001 1 00 >" ]
    then
        echo "Power down command received!"
        break
    else
        echo "Ill command received!"
        break
    fi

    echo $CAN_INPUT
done

destroy