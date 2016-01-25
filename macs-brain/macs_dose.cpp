/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 23/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: 12V DC Peristaltic Dosing Pump
*/

// Libraries
#include "macs_dose.h"


// Constructor
macs_dose::macs_dose() {
  pinMode(pumpOne12EnablePin, OUTPUT);
  pinMode(pumpOne1Apin, OUTPUT);
  pinMode(pumpOne2Apin, OUTPUT);
}

// Return status of the pump
bool macs_dose::getPumpOneStatus() {
  return pumpOneStatus;
}

// Drive pumpOne in clockwise direction: 1A -> L, 2A -> H
String macs_dose::startPumpOne() {
  digitalWrite(pumpOne12EnablePin, HIGH);
  pumpOne12EnablePinStatus = true;

  digitalWrite(pumpOne1Apin, LOW);
  pumpOne1ApinStatus = false;

  digitalWrite(pumpOne2Apin, HIGH);
  pumpOne2ApinStatus = true;

  pumpOneStatus = true;
  return "ON";
}

// Drive pumpOne to stop: 1A -> H, 2A -> H
String macs_dose::stopPumpOne() {
  digitalWrite(pumpOne12EnablePin, LOW);
  pumpOne12EnablePinStatus = false;

  digitalWrite(pumpOne1Apin, HIGH);
  pumpOne1ApinStatus = true;

  digitalWrite(pumpOne2Apin, HIGH);
  pumpOne2ApinStatus = true;

  pumpOneStatus = false;
  return "OFF";
}

