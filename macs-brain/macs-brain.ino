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
#include "macs_api.h"
#include "macs_resource.h"


// Declarations
#define serial_baud_rate 115200
// Timer1 interval 1sec => 1000000 microsec
#define timer1_interval 1000000

macs_display lcd_display;
macs_ph ph_meter;
macs_ec ec_meter;
macs_temperature temperature_meter;
macs_dose dosing;
macs_api api;
macs_resource res;

int pinButton = 8; //the pin where we connect the button
int LED = 2; //the pin we connect the LED


// Setup
void setup() {
  //   Initate the serial connections
  Serial.begin(serial_baud_rate);
  if (Serial) {
    Serial.println("==== Macsxperts Vertical Farming ====");
  }
  Timer1.initialize(timer1_interval);
  Timer1.attachInterrupt(sensingRoutine);  

  pinMode(pinButton, INPUT); //set the button pin as INPUT
  pinMode(LED, OUTPUT); //set the LED pin as OUTPUT

}


// ISR
void sensingRoutine(void)
{
  float temperature = temperature_meter.getTemperature();
  api.sendTemp(temperature);
  lcd_display.showTemperature(temperature);

  float ecValue = ec_meter.getEc(temperature);
  api.sendEc(ecValue);
  lcd_display.showEc(ecValue);
  lcd_display.showMsg(res.getText(dosing.balanceEc(ecValue)));

  float phValue = ph_meter.getPh();
  api.sendPh(phValue);
  lcd_display.showPh(phValue);
  lcd_display.showMsg(res.getText(dosing.balancePh(phValue)));
  
  Serial.println("");
}


// Main Loop
void loop() {
     digitalWrite(LED, LOW);  //write 0 or low to led pin
  int stateButton = digitalRead(pinButton); //read the state of the button
  if(stateButton == 1) { //if is pressed
     digitalWrite(LED, HIGH); //write 1 or HIGH to led pin
  } else { //if not pressed
     digitalWrite(LED, LOW);  //write 0 or low to led pin
  }
}
