#!/bin/sh
##############################################################
#  Script     : ssh-persisr.sh
#  Author     : Aravinth<me@aravinth.info>
#  Date       : 01/02/2016
##############################################################
# Description:
# - Persist the Reverse SSH Tunnel to serve Big Brother Nodejs Server
##############################################################

PID="$(ps aux | grep '3000:localhost:3000' | grep -v grep | awk '{print $2}')"

if [[ $? -ne 0 ]]; then
  echo "Creating new Reverse SSH-HTTP Tunnel"
  /usr/bin/ssh -N -R 3000:localhost:3000 macxpert@macsxperts.com &

  if [[ $? -eq 0 ]]; then
      echo "Reverse SSH-HTTP Tunnel is successfully created."
  else
      echo "Error occurred creating a Reverse SSH-HTTP Tunnel."
  fi
else
	echo "Reverse SSH-HTTP already exists."
fi