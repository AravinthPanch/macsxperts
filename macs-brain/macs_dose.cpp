/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 23/01/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: 12V DC Peristaltic Dosing Pump
*/

// Libraries
#include "macs_dose.h"
#include "macs_resource.h"   

macs_resource resource;

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

  pinMode(pumpFour34EnablePin, OUTPUT);
  pinMode(pumpFour3Apin, OUTPUT);
  pinMode(pumpFour4Apin, OUTPUT);
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

// Return status of the pump
bool macs_dose::getPumpFourStatus() {
  return pumpFourStatus;
}

// pH Logic
char* macs_dose::balancePh(float _phValue) {
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
      return "0xP1x1";
    }
    else if (!pumpOneStatus) {
      return "0xP1x0";
    }
  }
  // If pH is in the optimal range, stop the pump
  else if (phValue >= pHmin && phValue <= pHmax) {
    pumpOneTimer = 0;
    return stopPumpOne();
  }
  // Report if pH is below the minimum
  else if (phValue <= pHmin) {
    stopPumpOne();
    return "0xPHx1";
  }
}


// EC logic
char* macs_dose::balanceEc(float _ecValue) {
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
        startPumpFour();
        return "0xECx1";
      }
      else {
        stopPumpTwo();
        stopPumpThree();
        stopPumpFour();
        return "0xECx0";
      }
    }
    // Report the pump status
    else if (pumpTwoStatus && pumpThreeStatus) {
      return "0xECx1";
    }
    else if (!pumpTwoStatus && !pumpThreeStatus) {
      return "0xECx0";
    }
  }
// If ec is in the optimal range, stop the pump
  else if (ecValue >= ecMin && ecValue <= ecMax) {
    pumpTwoTimer = 0;
    stopPumpTwo();
    stopPumpThree();
    stopPumpFour();
    return "0xECx0";
  }
// Report if ec is above the minimum
  else if (ecValue >= ecMax) {
    stopPumpTwo();
    stopPumpThree();
    stopPumpFour();
    return "0xECx2";
  }
}


char* macs_dose::startPumpOne() {
  if (!pumpOneStatus) {
    startPump(pumpOne12EnablePin, &pumpOne12EnablePinStatus,
              pumpOne1Apin, &pumpOne1ApinStatus,
              pumpOne2Apin, &pumpOne2ApinStatus,
              &pumpOneStatus, 1);
  }
  return "0xP1x1";
}

char* macs_dose::stopPumpOne() {
  if (pumpOneStatus) {
    stopPump(pumpOne12EnablePin, &pumpOne12EnablePinStatus,
             pumpOne1Apin, &pumpOne1ApinStatus,
             pumpOne2Apin, &pumpOne2ApinStatus,
             &pumpOneStatus, 1);
  }
  return "0xP1x0";
}


String macs_dose::startPumpTwo() {
  if (!pumpTwoStatus) {
    startPump(pumpTwo34EnablePin, &pumpTwo34EnablePinStatus,
              pumpTwo3Apin, &pumpTwo3ApinStatus,
              pumpTwo4Apin, &pumpTwo4ApinStatus,
              &pumpTwoStatus, 2);
  }
  return "0xP2x1";
}


String macs_dose::stopPumpTwo() {
  if (pumpTwoStatus) {
    stopPump(pumpTwo34EnablePin, &pumpTwo34EnablePinStatus,
             pumpTwo3Apin, &pumpTwo3ApinStatus,
             pumpTwo4Apin, &pumpTwo4ApinStatus,
             &pumpTwoStatus, 2);
  }
  return "0xP2x0";
}


String macs_dose::startPumpThree() {
  if (!pumpThreeStatus) {
    startPump(pumpThree12EnablePin, &pumpThree12EnablePinStatus,
              pumpThree1Apin, &pumpThree1ApinStatus,
              pumpThree2Apin, &pumpThree2ApinStatus,
              &pumpThreeStatus, 3);
  }
  return "0xP3x1";
}


String macs_dose::stopPumpThree() {
  if (pumpThreeStatus) {
    stopPump(pumpThree12EnablePin, &pumpThree12EnablePinStatus,
             pumpThree1Apin, &pumpThree1ApinStatus,
             pumpThree2Apin, &pumpThree2ApinStatus,
             &pumpThreeStatus, 3);
  }
  return "0xP3x0";
}


String macs_dose::startPumpFour() {
  if (!pumpFourStatus) {
    startPump(pumpFour34EnablePin, &pumpFour34EnablePinStatus,
              pumpFour3Apin, &pumpFour3ApinStatus,
              pumpFour4Apin, &pumpFour4ApinStatus,
              &pumpFourStatus, 4);
  }
  return "0xP4x1";
}

String macs_dose::stopPumpFour() {
  if (pumpFourStatus) {
    stopPump(pumpFour34EnablePin, &pumpFour34EnablePinStatus,
             pumpFour3Apin, &pumpFour3ApinStatus,
             pumpFour4Apin, &pumpFour4ApinStatus,
             &pumpFourStatus, 4);
  }
  return "0xP4x0";
}


// -------------------- Drive Motors --------------------//

// Drive pump in clockwise direction (Pump is connected as upper connector
// is Positive and lower connector is Negative): 1A -> H, 2A -> L
void macs_dose::startPump(int enablePin, bool* enablePinVar,
                          int firstPin, bool* firstPinVar,
                          int secondPin, bool* secondPinVar,
                          bool* pumpStatus, int pumpNumber) {



  digitalWrite(enablePin, HIGH);
  *enablePinVar = true;

  digitalWrite(firstPin, HIGH);
  *firstPinVar = true;

  digitalWrite(secondPin, LOW);
  *secondPinVar = false;

  *pumpStatus = true;


  Serial.print(millis() / 1000.0, 3);
  Serial.print(" : ");
  switch (pumpNumber) {
  case 1:
    Serial.println(resource.getText("0xP1x11"));
    break;
  case 2:
    Serial.println(resource.getText("0xP2x11"));
    break;
  case 3:
    Serial.println(resource.getText("0xP3x11"));
    break;
  case 4:
    Serial.println(resource.getText("0xP4x11"));
    break;
  }
}


// Drive pump to stop: 1A -> H, 2A -> H
void macs_dose::stopPump(int enablePin, bool* enablePinVar,
                         int firstPin, bool* firstPinVar,
                         int secondPin, bool* secondPinVar,
                         bool* pumpStatus, int pumpNumber) {

  digitalWrite(enablePin, LOW);
  *enablePinVar = false;

  digitalWrite(firstPin, HIGH);
  *firstPinVar = true;

  digitalWrite(secondPin, HIGH);
  *secondPinVar = true;

  *pumpStatus = false;

  
  Serial.print(millis() / 1000.0, 3);
  Serial.print(" : ");
  switch (pumpNumber) {
  case 1:
    Serial.println(resource.getText("0xP1x00"));
    break;
  case 2:
    Serial.println(resource.getText("0xP2x00"));
    break;
  case 3:
    Serial.println(resource.getText("0xP3x00"));
    break;
  case 4:
    Serial.println(resource.getText("0xP4x00"));
    break;
  }
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
