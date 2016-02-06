/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 23/01/16.
   Project: Macsxperts Vertical Farming Solutions
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

// Return status of the pump
bool macs_dose::getPumpTwoStatus() {
  return pumpTwoStatus;
}

// Return status of the pump
bool macs_dose::getPumpThreeStatus() {
  return pumpThreeStatus;
}


// pH Logic
String macs_dose::balancePh(float phValue) {
  if (phValue < 8.0) {
    startPumpOne(5);
    return "P1: ON";
  }
  else {
    stopPumpOne();
    return "P1: OFF";
  }
}


// EC logic
String macs_dose::balanceEc(float ecValue) {
  if (ecValue < 1200) {
    startPumpTwo(5);
    startPumpThree(5);
    return "P2,3: ON";
  }
  else {
    stopPumpTwo();
    stopPumpThree();
    return "P2,3: OFF";
  }
}


// Drive pump in clockwise direction (Pump is connected as upper connector
// is Positive and lower connector is Negative): 1A -> H, 2A -> L
void macs_dose::startPump(int enablePin, bool* enablePinVar,
                          int firstPin, bool* firstPinVar,
                          int secondPin, bool* secondPinVar,
                          bool* pumpStatus) {

  Serial.print(millis() / 1000.0, 3);
  Serial.print(" : ");
  Serial.println("PumpOne is ON");

  digitalWrite(enablePin, HIGH);
  *enablePinVar = true;

  digitalWrite(firstPin, HIGH);
  *firstPinVar = true;

  digitalWrite(secondPin, LOW);
  *secondPinVar = false;

  *pumpStatus = true;
}


// Drive pump to stop: 1A -> H, 2A -> H
void macs_dose::stopPump(int enablePin, bool* enablePinVar,
                         int firstPin, bool* firstPinVar,
                         int secondPin, bool* secondPinVar,
                         bool* pumpStatus) {

  Serial.print(millis() / 1000.0, 3);
  Serial.print(" : ");
  Serial.println("PumpOne is OFF");

  digitalWrite(enablePin, LOW);
  *enablePinVar = false;

  digitalWrite(firstPin, HIGH);
  *firstPinVar = true;

  digitalWrite(secondPin, HIGH);
  *secondPinVar = true;

  *pumpStatus = true;
}


void macs_dose::startPumpOne(int seconds) {
  if (pumpOneTimer <= seconds || seconds == 0) {
    pumpOneTimer++;
    if (!pumpOneStatus) {
      startPump(pumpOne12EnablePin, &pumpOne12EnablePinStatus,
                pumpOne1Apin, &pumpOne1ApinStatus,
                pumpOne2Apin, &pumpOne2ApinStatus,
                &pumpOneStatus);
    }
  }
}


void macs_dose::stopPumpOne() {
  pumpOneTimer = 1;
  if (pumpOneStatus) {
    stopPump(pumpOne12EnablePin, &pumpOne12EnablePinStatus,
             pumpOne1Apin, &pumpOne1ApinStatus,
             pumpOne2Apin, &pumpOne2ApinStatus,
             &pumpOneStatus);
  }
}


void macs_dose::startPumpTwo(int seconds) {
  if (pumpTwoTimer <= seconds || seconds == 0) {
    pumpTwoTimer++;
    if (!pumpTwoStatus) {
      startPump(pumpTwo34EnablePin, &pumpTwo34EnablePinStatus,
                pumpTwo3Apin, &pumpTwo3ApinStatus,
                pumpTwo4Apin, &pumpTwo4ApinStatus,
                &pumpTwoStatus);
    }
  }
}


void macs_dose::stopPumpTwo() {
  pumpTwoTimer = 1;
  if (pumpTwoStatus) {
    stopPump(pumpTwo34EnablePin, &pumpTwo34EnablePinStatus,
             pumpTwo3Apin, &pumpTwo3ApinStatus,
             pumpTwo4Apin, &pumpTwo4ApinStatus,
             &pumpTwoStatus);
  }
}


void macs_dose::startPumpThree(int seconds) {
  if (pumpThreeTimer <= seconds || seconds == 0) {
    pumpThreeTimer++;
    if (!pumpThreeStatus) {
      startPump(pumpThree12EnablePin, &pumpThree12EnablePinStatus,
                pumpThree1Apin, &pumpThree1ApinStatus,
                pumpThree2Apin, &pumpThree2ApinStatus,
                &pumpThreeStatus);
    }
  }
}


void macs_dose::stopPumpThree() {
  pumpThreeTimer = 1;
  if (pumpThreeStatus) {
    stopPump(pumpThree12EnablePin, &pumpThree12EnablePinStatus,
             pumpThree1Apin, &pumpThree1ApinStatus,
             pumpThree2Apin, &pumpThree2ApinStatus,
             &pumpThreeStatus);
  }
}

void macs_dose::setTestPumpStatus(bool status) {
  testPumpStatus = true;
}

String macs_dose::testPump(int pumpNr, int seconds) {
  if (testPumpTimer <= seconds & testPumpStatus) {
    testPumpTimer++;

    switch (pumpNr) {
      case 1:
        startPumpOne(seconds);
        return "P1: ON";
        break;
      case 2:
        startPumpTwo(seconds);
        return "P2: ON";
        break;
      case 3:
        startPumpThree(seconds);
        return "P3: ON";
        break;
    }
  }
  else {
    testPumpStatus = false;
    testPumpTimer = 1;

    switch (pumpNr) {
      case 1:
        stopPumpOne();
        return "P1: OFF";
        break;
      case 2:
        stopPumpTwo();
        return "P2: OFF";
        break;
      case 3:
        stopPumpThree();
        return "P3: OFF";
        break;
    }
  }
}
