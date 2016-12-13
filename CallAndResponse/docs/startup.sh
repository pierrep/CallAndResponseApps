#!/bin/bash
sudo ifdown eth0
sudo ifup eth0
sleep 120
#cd /home/pi/code/of_v0.9.0_linuxarmv7l_release/apps/CallAndResponseApps/CallAndResponse/bin
cd /home/pi/code/of_v0.9.3_linuxarmv6l_release/apps/CallAndResponseApps/CallAndResponse/bin
./CallAndResponse


