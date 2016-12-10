#!/bin/bash

# to run with bash -x GPS_init.sh
# after connecting the GPS to /dev/ttyS0

echo 'Updating USB port baud rate to 9600 ...'
stty -F /dev/ttyS0 9600
echo '...Done !'

sleep 1

echo 'Tell GPS to return only GPGGA and GPRMC lines...'
( stty raw speed 9600 >&2; echo -ne '$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n') > /dev/ttyS0 <&1
echo '...Done'

sleep 1

echo 'Set GPS baud rate to 115200...'
( stty raw speed 9600 >&2; echo -ne '$PMTK251,115200*1F\r\n') > /dev/ttyS0 <&1
echo '...Done'

sleep 1

echo 'Updating USB port baud rate to 115200...'
stty -F /dev/ttyS0 115200
echo '...Done !'

sleep 1

echo 'Set GPS output frequency to 10Hz...'
( stty raw speed 115200 >&2; echo -ne '$PMTK220,100*2F\r\n') > /dev/ttyS0 <&1
echo '...Done !'

sleep 1

echo 'Test'
echo ''
echo ''
stty raw -echo < /dev/ttyS0; cat -vte /dev/ttyS0 

