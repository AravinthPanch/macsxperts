/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 23/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: 12V DC Peristaltic Dosing Pump
*/

#include "macs_dose.h"

macs_dose::macs_dose() {
  pinMode(pumpOne12EnablePin, OUTPUT);
  pinMode(pumpOne1Apin, OUTPUT);
  pinMode(pumpOne2Apin, OUTPUT);
}

int macs_dose::holaDose() {
  counter++;
  return counter;
}

void macs_dose::enablePumpOne(bool setStatus) {
  if (setStatus && pumpOne12EnablePinStatus == false) {
    digitalWrite(pumpOne12EnablePin, HIGH);
    pumpOne12EnablePinStatus = HIGH;
  }
  else if (pumpOne12EnablePinStatus && setStatus == false) {
    digitalWrite(pumpOne12EnablePin, LOW);
    pumpOne12EnablePinStatus = LOW;
  }
}

bool macs_dose::stopPumpOne() {
  Serial.println("Motor Stop");
  enablePumpOne(true);
  digitalWrite(pumpOne1Apin, HIGH);
  digitalWrite(pumpOne2Apin, HIGH);
  return true;
}

bool macs_dose::dosePumpOne() {
  Serial.println("Turn right");
  enablePumpOne(true);
  digitalWrite(pumpOne1Apin, LOW);
  digitalWrite(pumpOne2Apin, HIGH);
  return true;
}
