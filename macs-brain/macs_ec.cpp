/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 25/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: DFRobot Analog EC Meter DFR0300
*/

// Libraries
#include "macs_ec.h"


// Test routine
int macs_ec::holaEc() {
  counter += 0.01;
  return counter;
}

