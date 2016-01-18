/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 04/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
*/

// Third party Libraries
#include <TimerOne.h>
#include "Print.h"

// Libraries
#include "aero_ph.h"


// Declarations
long timer1_interval = 1000000;



// Setup
void setup() {
  // Initate the serial connections
  Serial.begin(9600);
  if (Serial) {
    Serial.println("==== Macsxperts Aeroponics Vertical Farming ====");
  }

  // Initate timer to 1sec => 1000000 microsec interval
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(senseRoutine);
}


// ISR
aero_ph ph_meter(&Serial);

void senseRoutine(void)
{
  Serial.println(ph_meter.getPh());
}


// Main Loop
void loop() {
}
