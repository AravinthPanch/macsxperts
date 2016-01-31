/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 18/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: DFRobot pH Pro (SEN0169)
*/

// Libraries
#include "macs_ph.h"


// Read analog values from sensor and calculate the phVoltage (5V) and pH value
float macs_ph::getPh() {
  static float phValue, phVoltage;
  for (int i = 0; i < phArrayLenth ; i ++) {    
    phArray[phArrayIndex++]  = analogRead(phSensorPin);
  }
  phArrayIndex = 0;
  phVoltage = phArrayAverage(phArray, phArrayLenth) * 5.0 / 1024;
  phValue = 3.5 * phVoltage + phOffset;
  return phValue;
}

// Calculate the average value of array
double macs_ph::phArrayAverage(int* inputArray, int arrayLength) {
  double avg;
  long total = 0;

  if (arrayLength <= 0) {
    return 0;
  }
  else {
    for (int i = 0; i < arrayLength; i++) {
      total += inputArray[i];
    }
    avg = total / arrayLength;
    return avg;
  }
}

// Test routine
int macs_ph::holaPh() {
  counter++;
  return counter;
}

