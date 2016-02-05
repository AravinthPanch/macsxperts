/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 04/01/16.
   Project: Macsxperts Vertical Farming Solutions
*/

// Libraries
#include <TimerOne.h>
#include "Print.h"
#include "macs_display.h"
#include "macs_ph.h"
#include "macs_ec.h"
#include "macs_dose.h"
#include "macs_temperature.h"

// Declarations
#define serial_baud_rate 115200
// Timer1 interval 1sec => 1000000 microsec
#define timer1_interval 1000000

macs_display lcd_display;
macs_ph ph_meter;
macs_ec ec_meter;
macs_temperature temperature_meter;
macs_dose dosing_pump;


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

  float temperature = temperature_meter.getTemperature();
  lcd_display.showTemperature(temperature);

  float ecValue = ec_meter.getEc(temperature);
  dosing_pump.balanceEc(ecValue);
  lcd_display.showEc(ecValue);

  float phValue = ph_meter.getPh();
  lcd_display.showPh(phValue);
  
  lcd_display.showMsg(dosing_pump.balancePh(phValue));
}


// Main Loop
void loop() {

}
