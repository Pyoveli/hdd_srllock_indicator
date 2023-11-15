#!/bin/bash

# Path to sedleds cmd
SETLEDS_CMD=/usr/bin/setleds

# Check interval seconds
CHECKINTERVAL=0.1

# console
CONSOLE=/dev/console

#indicator to use scroll lock led
INDICATOR=scroll
getVmstat() {
  cat /proc/vmstat | grep -E "pgpgin|pgpgout"
}
#turn led on
function led_on()
{
    ${SETLEDS_CMD} -L +${INDICATOR} < ${CONSOLE}
}
#turn led off
function led_off()
{
    ${SETLEDS_CMD} -L -${INDICATOR} < ${CONSOLE}
}
# init vars
NEW=$(getVmstat)
OLD=$(getVmstat)
##
while true ; do
  sleep $CHECKINTERVAL # slowdown a bit
  # get status
  NEW=$(getVmstat)
  #compare state
  if [ "$NEW" = "$OLD" ]; then
    led_off ## if no change, led off
  else
    led_on  ## if change, led on
  fi
  OLD=$NEW
done
