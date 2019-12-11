#!/bin/bash
# Program:       CAN_button.sh
# Creator:       Samuel Duclos
# Comments:      This file is directly invoked using source.
#                This prevents file descriptors from getting
#                closed prematurely with an exiting subshell.
# Documentation: https://github.com/linux-can/can-utils/blob/master/bcmserver.c
# Example usage: sudo --prompt=temppwd su -c 'source /home/debian/CAN_button.sh' --preserve-environment

# Modifiable variables.
INTERFACE_TYPE=can
BITRATE=50000

# Non-modifiable variables.
INTERFACE=$INTERFACE_TYPE'0'
BITRATE='bitrate '$BITRATE
SOCKET=/dev/tcp/127.0.0.1/28600
GREEN_LED=/sys/class/leds/green
RED_LED=/sys/class/leds/red
GPIO=/sys/class/gpio
BUTTON=$GPIO/gpio69
MOTOR_STATE='01'

# Ensure kernel modules are loaded.
modprobe vcan

# Set green LED to persistent mode.
echo 'none' > $GREEN_LED/trigger
echo 'none' > $RED_LED/trigger

# Turn green LED on and red LED off.
echo '255' > $GREEN_LED/brightness
echo '0' > $RED_LED/brightness

# Configure user button 2 (PAUSE_BTN, GPIO2_5).
echo 69 > $GPIO/export
echo 'rising' > $BUTTON/edge

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
    ip link add dev $INTERFACE type $INTERFACE_TYPE
fi

# Making sure the interface is up.
eval "ip link set up $INTERFACE type $INTERFACE_TYPE $BITRATE"

# Starting CAN broadcast manager.
bcmserver &
PID_SERVER=$!
sleep 1 # Waiting for server to boot.

# Linking socket to file descriptor to be used.
exec {FILE_DESCRIPTOR}<>$SOCKET

function destroy {
    # Kill server.
    kill $PID_SERVER

    # Kill file descriptor.
    exec {FILE_DESCRIPTOR}>&-

    # Destroy network interface.
    ip link set down $INTERFACE
    ip link delete dev $INTERFACE type $INTERFACE_TYPE

    # Configure user button 2 (PAUSE_BTN, GPIO2_5).
    echo 'none' > $BUTTON/edge
    echo 69 > $GPIO/unexport

    # Turn green LED off and red LED on.
    echo '0' > $GREEN_LED/brightness
    echo '255' > $RED_LED/brightness
}

# Let kernel trap shell exit interruptions.
trap destroy SIGTERM
trap destroy SIGINT
trap destroy SIGHUP

# Send commands to server through file descriptor to socket:

# < INTERFACE RECEIVE_FROM DELAY_SEC DELAY_US HEX_ADDRESS N_BYTES FILTER >
echo "<${INTERFACE} R 0 0 001 1 FF>" >&$FILE_DESCRIPTOR

EDGE_OLD=$(cat /proc/interrupts | grep gpiolib)

# Leave time to setup other devices.
sleep 8

# Main loop.
while true :
do
    # Read server output from file descriptor.
    read -t 0.001 -d '' -u $FILE_DESCRIPTOR -r CAN_INPUT

    if [ "$CAN_INPUT" != '' ]
    then
        echo $CAN_INPUT
    fi

    if [ "$CAN_INPUT" == "< ${INTERFACE} 001 1 01 >" ] || \
       [ "$CAN_INPUT" == "< ${INTERFACE} 001 1 03 >" ] || \
       [ "$CAN_INPUT" == '' ]
    then
        sleep 0.05

        EDGE=$(cat /proc/interrupts | grep gpiolib)

        if [ "$EDGE" != "$EDGE_OLD" ]
        then
            echo "User button pressed!"
            EDGE_OLD=$EDGE

            if [ "$MOTOR_STATE" == '03' ]
            then
                MOTOR_STATE='01'
                echo "<${INTERFACE} S 0 0 003 1 01>" >&$FILE_DESCRIPTOR
                echo 'Motor state: 01'

            else
                MOTOR_STATE='03'
                echo "<${INTERFACE} S 0 0 003 1 03>" >&$FILE_DESCRIPTOR
                echo 'Motor state: 03'
            fi
        fi

    elif [ "$CAN_INPUT" == "< ${INTERFACE} 001 1 00 >" ]
    then
        echo "Power down command received!"
        break

    else
        echo "Ill command received!"
        break
    fi

done

destroy
