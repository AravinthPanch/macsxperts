#!/bin/sh
##############################################################
#  Script     : time-lapse.sh
#  Author     : Aravinth<me@aravinth.info>
#  Date       : 30/01/2016
##############################################################
# Description:
# - To take fotos in a given interval to create a time lapse
# of the growing plants
##############################################################

DATE=$(date +"%Y-%m-%d-%H-%M")

ps aux | grep -i mjpg_streamer | grep -v grep | awk {'print $2'} | xargs kill -9;

sleep 5;

fswebcam -r 1280x720 /home/aravinth/macsxperts/macs-panel/time-lapse/images/$DATE.jpg;

