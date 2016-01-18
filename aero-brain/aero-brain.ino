/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 04/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
*/

// Libraries
#include <TimerOne.h>
#include "Print.h"
#include "aero_ph.h"

// Declarations
int serial_baud_rate = 9600;
// Initate timer to 1sec => 1000000 microsec interval
long timer1_interval = 1000000;
char str_header[] = "==== Macsxperts Aeroponics Vertical Farming ====";
aero_ph ph_meter;

// Setup
void setup() {
  // Initate the serial connections
  Serial.begin(serial_baud_rate);
  if (Serial) {
    Serial.println(str_header);
  }
  Timer1.initialize(timer1_interval);
  Timer1.attachInterrupt(sensingRoutine);
}

// ISR
void sensingRoutine(void)
{
  Serial.println(ph_meter.getPh());
}

// Main Loop
void loop() {
}
