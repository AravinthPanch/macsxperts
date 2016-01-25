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
#include "macs_display.h"

// Declarations
#define serial_baud_rate 9600
// Timer1 interval 1sec => 1000000 microsec
#define timer1_interval 1000000

macs_ph ph_meter;
macs_dose dosing_pump;
macs_display lcd_display;

// Setup
void setup() {
  //   Initate the serial connections
  Serial.begin(serial_baud_rate);
  if (Serial) {
    Serial.println("==== Macsxperts Vertical Farming ====");
  }
  Timer1.initialize(timer1_interval);
  Timer1.attachInterrupt(sensingRoutine);
}


// ISR
void sensingRoutine(void)
{
  //    if (!dosing_pump.getPumpOneStatus()) {
  //      Serial.println("PumpOne is ON");
  //      lcd_display.showMsg("PumpOne is ON");
  //      dosing_pump.startPumpOne();
  //    }
  //    else {
  //      Serial.println("PumpOne is OFF");
  //      lcd_display.showMsg("PumpOne is OFF");
  //      dosing_pump.stopPumpOne();
  //    }

  lcd_display.showPh(ph_meter.getPh());
}


// Main Loop
void loop() {
}
