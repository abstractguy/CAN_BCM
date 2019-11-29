# Library functions for the BeagleBone.

INTERFACE="${INTERFACE_TYPE}0"
SOCKET=/dev/tcp/127.0.0.1/28600
LEDS=/sys/class/leds
SYNC=test

function LEDS_OFF {
    for LED in $(ls $LEDS); do
        echo "none" > $LEDS/$LED/trigger
        echo "0" > $LEDS/$LED/brightness
    done
}

function LEDS_ON {
    for LED in $(ls $LEDS); do
        echo "none" > $LEDS/$LED/trigger
        echo "255" > $LEDS/$LED/brightness
    done
}

# Clean up function.
function safe_exit {
    echo "<${INTERFACE} X 0 0 010 0 00>" >&3 # Delete receiver.
    echo "<${INTERFACE} D 0 0 010 0 00>" >&3 # Delete cyclic sender.
    echo "<${INTERFACE} S 0 0 010 1 00>" >&3 # Send power off command.
    sleep $DELAY
    kill $PID_INPUT
    exec 3>&-
    kill $PID_SERVER
    ifconfig $INTERFACE down
    ip link delete dev $INTERFACE type $INTERFACE_TYPE
}
