/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 18/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: DF Robot pH Pro (SEN0169)
*/

#include "aero_ph.h"

int aero_ph::holaPh() {
  counter++;
  return counter;
}

// Read analog values from sensor 40 times and calculate the phVoltage (5V) and pH value
float aero_ph::getPh() {
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
double aero_ph::phArrayAverage(int* inputArray, int arrayLength) {
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
