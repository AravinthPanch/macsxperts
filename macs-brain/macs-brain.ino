/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 04/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
*/

// Libraries
#include <TimerOne.h>
#include "Print.h"
#include "macs_ph.h"
#include "macs_dose.h"

// Declarations
int serial_baud_rate = 9600;
// Initate timer to 1sec => 1000000 microsec interval
long timer1_interval = 3000000;
char str_header[] = "==== Macsxperts Aeroponics Vertical Farming ====";
macs_ph ph_meter;
macs_dose dosing_pump;
bool pumpOneStatus = false;


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
  if (!pumpOneStatus) {
    bool rv = dosing_pump.dosePumpOne();
    if (rv) {
      pumpOneStatus = true;
    }
  }
  else {
    bool rv = dosing_pump.stopPumpOne();
    if (rv) {
      pumpOneStatus = false;
    }
  }


}

// Main Loop
void loop() {
}
