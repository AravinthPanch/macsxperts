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

  pinMode(pumpTwo34EnablePin, OUTPUT);
  pinMode(pumpTwo3Apin, OUTPUT);
  pinMode(pumpTwo4Apin, OUTPUT);

  pinMode(pumpThree12EnablePin, OUTPUT);
  pinMode(pumpThree1Apin, OUTPUT);
  pinMode(pumpThree2Apin, OUTPUT);
}

// Return status of the pump
bool macs_dose::getPumpOneStatus() {
  return pumpOneStatus;
}

// Drive pumpOne in clockwise direction (Pump is connected as upper connector is Positive and lower connector is Negative): 1A -> H, 2A -> L
String macs_dose::startPumpOne() {
  digitalWrite(pumpOne12EnablePin, HIGH);
  pumpOne12EnablePinStatus = true;

  digitalWrite(pumpOne1Apin, HIGH);
  pumpOne1ApinStatus = false;

  digitalWrite(pumpOne2Apin, LOW);
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

// Return status of the pump
bool macs_dose::getPumpTwoStatus() {
  return pumpTwoStatus;
}

// Drive pumpTwo in clockwise direction (Pump is connected as upper connector is Positive and lower connector is Negative): 3A -> H, 4A -> L
String macs_dose::startPumpTwo() {
  digitalWrite(pumpTwo34EnablePin, HIGH);
  pumpTwo34EnablePinStatus = true;

  digitalWrite(pumpTwo3Apin, HIGH);
  pumpTwo3ApinStatus = false;

  digitalWrite(pumpTwo4Apin, LOW);
  pumpTwo4ApinStatus = true;

  pumpTwoStatus = true;
  return "ON";
}

// Drive pumpTwo to stop: 3A -> H, 4A -> H
String macs_dose::stopPumpTwo() {
  digitalWrite(pumpTwo34EnablePin, LOW);
  pumpTwo34EnablePinStatus = false;

  digitalWrite(pumpTwo3Apin, HIGH);
  pumpTwo3ApinStatus = true;

  digitalWrite(pumpTwo4Apin, HIGH);
  pumpTwo4ApinStatus = true;

  pumpTwoStatus = false;
  return "OFF";
}

// Return status of the pump
bool macs_dose::getPumpThreeStatus() {
  return pumpThreeStatus;
}

// Drive pumpThree in clockwise direction (Pump is connected as upper connector is Positive and lower connector is Negative): 1A -> H, 2A -> L
String macs_dose::startPumpThree() {
  digitalWrite(pumpThree12EnablePin, HIGH);
  pumpThree12EnablePinStatus = true;

  digitalWrite(pumpThree1Apin, HIGH);
  pumpThree1ApinStatus = false;

  digitalWrite(pumpThree2Apin, LOW);
  pumpThree2ApinStatus = true;

  pumpThreeStatus = true;
  return "ON";
}

// Drive pumpThree to stop: 1A -> H, 2A -> H
String macs_dose::stopPumpThree() {
  digitalWrite(pumpThree12EnablePin, LOW);
  pumpThree12EnablePinStatus = false;

  digitalWrite(pumpThree1Apin, HIGH);
  pumpThree1ApinStatus = true;

  digitalWrite(pumpThree2Apin, HIGH);
  pumpThree2ApinStatus = true;

  pumpThreeStatus = false;
  return "OFF";
}

// Test run of pumps
void macs_dose::pumpsTest(){
    if (!this->getPumpOneStatus()) {
    Serial.print(millis() / 1000.0, 3);
    Serial.print(" : ");
    Serial.println("PumpOne is ON");
    //lcd_display.showMsg("PumpOne is ON");
    this->startPumpOne();
  }
  else {
    Serial.print(millis() / 1000.0, 3);
    Serial.print(" : ");
    Serial.println("PumpOne is OFF");
    //lcd_display.showMsg("PumpOne is OFF");
    this->stopPumpOne();
  }

  if (!this->getPumpTwoStatus()) {
    Serial.print(millis() / 1000.0, 3);
    Serial.print(" : ");
    Serial.println("PumpTwo is ON");
    //lcd_display.showMsg("PumpTwo is ON");
    this->startPumpTwo();
  }
  else {
    Serial.print(millis() / 1000.0, 3);
    Serial.print(" : ");
    Serial.println("PumpTwo is OFF");
    //lcd_display.showMsg("PumpTwo is OFF");
    this->stopPumpTwo();
  }

  if (!this->getPumpThreeStatus()) {
    Serial.print(millis() / 1000.0, 3);
    Serial.print(" : ");
    Serial.println("PumpThree is ON");
    //lcd_display.showMsg("PumpThree is ON");
    this->startPumpThree();
  }
  else {
    Serial.print(millis() / 1000.0, 3);
    Serial.print(" : ");
    Serial.println("PumpThree is OFF");
    //lcd_display.showMsg("PumpThree is OFF");
    this->stopPumpThree();
  }
}
