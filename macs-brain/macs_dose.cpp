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
String macs_dose::balancePh(float _phValue) {
  phValue = _phValue;

  // If pH is above the maximum,
  // start and stop the pump in the given interval,
  // till optima pH is achieved
  if (phValue >= pHmax) {
    pumpOneTimer++;

    if (pumpOneTimer >= phDosingInterval) {
      pumpOneTimer = 0;

      // If the pump is not running, start it,
      // Else stop it
      if (!pumpOneStatus) {
        return startPumpOne();
      }
      else {
        return stopPumpOne();
      }
    }
    // Report the pump status
    else if (pumpOneStatus) {
      return "P1: ON";
    }
    else if (!pumpOneStatus) {
      return "P1: OFF";
    }
  }
  // If pH is in the optimal range, stop the pump
  else if (phValue >= pHmin && phValue <= pHmax) {
    pumpOneTimer = 0;
    return stopPumpOne();
  }
  // Report if pH is below the minimum
  else if (phValue <= pHmin) {
    return "Low pH";
  }
}


// EC logic
String macs_dose::balanceEc(float _ecValue) {
  ecValue = _ecValue;

// If EC is below the minimum,
// start and stop the pump in the given interval,
// till optima ec is achieved
  if (ecValue <= ecMin) {
    pumpTwoTimer++;

    if (pumpTwoTimer >= ecDosingInterval) {
      pumpTwoTimer = 0;

      // If the pump is not running, start it,
      // Else stop it
      if (!pumpTwoStatus && !pumpThreeStatus) {
        startPumpTwo();
        startPumpThree();
        return "P2,3: ON";
      }
      else {
        stopPumpTwo();
        stopPumpThree();
        return "P2,3: OFF";
      }
    }
    // Report the pump status
    else if (pumpTwoStatus && pumpThreeStatus) {
      return "P2,3: ON";
    }
    else if (!pumpTwoStatus && !pumpThreeStatus) {
      return "P2,3: OFF";
    }
  }
// If ec is in the optimal range, stop the pump
  else if (ecValue >= ecMin && ecValue <= ecMax) {
    pumpTwoTimer = 0;
    stopPumpTwo();
    stopPumpThree();
    return "P2,3: OFF";
  }
// Report if ec is above the minimum
  else if (ecValue >= ecMax) {
    return "High EC";
  }
}


String macs_dose::startPumpOne() {
  if (!pumpOneStatus) {
    startPump(pumpOne12EnablePin, &pumpOne12EnablePinStatus,
              pumpOne1Apin, &pumpOne1ApinStatus,
              pumpOne2Apin, &pumpOne2ApinStatus,
              &pumpOneStatus, 1);
  }
  return "P1: ON";
}

String macs_dose::stopPumpOne() {
  if (pumpOneStatus) {
    stopPump(pumpOne12EnablePin, &pumpOne12EnablePinStatus,
             pumpOne1Apin, &pumpOne1ApinStatus,
             pumpOne2Apin, &pumpOne2ApinStatus,
             &pumpOneStatus, 1);
  }
  return "P1: OFF";
}


String macs_dose::startPumpTwo() {
  if (!pumpTwoStatus) {
    startPump(pumpTwo34EnablePin, &pumpTwo34EnablePinStatus,
              pumpTwo3Apin, &pumpTwo3ApinStatus,
              pumpTwo4Apin, &pumpTwo4ApinStatus,
              &pumpTwoStatus, 2);
  }
  return "P2: ON";
}


String macs_dose::stopPumpTwo() {
  if (pumpTwoStatus) {
    stopPump(pumpTwo34EnablePin, &pumpTwo34EnablePinStatus,
             pumpTwo3Apin, &pumpTwo3ApinStatus,
             pumpTwo4Apin, &pumpTwo4ApinStatus,
             &pumpTwoStatus, 2);
  }
  return "P2: OFF";
}


String macs_dose::startPumpThree() {
  if (!pumpThreeStatus) {
    startPump(pumpThree12EnablePin, &pumpThree12EnablePinStatus,
              pumpThree1Apin, &pumpThree1ApinStatus,
              pumpThree2Apin, &pumpThree2ApinStatus,
              &pumpThreeStatus, 3);
  }
  return "P3: ON";
}


String macs_dose::stopPumpThree() {
  if (pumpThreeStatus) {
    stopPump(pumpThree12EnablePin, &pumpThree12EnablePinStatus,
             pumpThree1Apin, &pumpThree1ApinStatus,
             pumpThree2Apin, &pumpThree2ApinStatus,
             &pumpThreeStatus, 3);
  }
  return "P3: OFF";
}


// -------------------- Drive Motors --------------------//

// Drive pump in clockwise direction (Pump is connected as upper connector
// is Positive and lower connector is Negative): 1A -> H, 2A -> L
void macs_dose::startPump(int enablePin, bool* enablePinVar,
                          int firstPin, bool* firstPinVar,
                          int secondPin, bool* secondPinVar,
                          bool* pumpStatus, int pumpNumber) {

  Serial.print(millis() / 1000.0, 3);
  Serial.print(" : P");
  Serial.print(pumpNumber);
  Serial.println(" is switched ON");

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
                         bool* pumpStatus, int pumpNumber) {

  Serial.print(millis() / 1000.0, 3);
  Serial.print(" : P");
  Serial.print(pumpNumber);
  Serial.println(" is switched OFF");

  digitalWrite(enablePin, LOW);
  *enablePinVar = false;

  digitalWrite(firstPin, HIGH);
  *firstPinVar = true;

  digitalWrite(secondPin, HIGH);
  *secondPinVar = true;

  *pumpStatus = false;
}

// -------------------- Test Functions --------------------//

void macs_dose::setTestPumpStatus(bool status) {
  testPumpStatus = true;
}

String macs_dose::testPump(int pumpNr, int seconds) {
  if (testPumpTimer <= seconds & testPumpStatus) {
    testPumpTimer++;

    switch (pumpNr) {
    case 1:
      startPumpOne();
      return "P1: ON";
      break;
    case 2:
      startPumpTwo();
      return "P2: ON";
      break;
    case 3:
      startPumpThree();
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
