#!/bin/bash

/bin/pidof ssh

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