/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 25/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: DFRobot Analog EC Meter DFR0300
*/

// Libraries
#include "macs_ec.h"


float macs_ec::getEc(float temperature) {
  static float ecValue, ecVoltage;
  for (int i = 0; i < ecArrayLenth ; i ++) {
    ecArray[ecArrayIndex++]  = analogRead(ecSensorPin);
  }
  ecArrayIndex = 0;
  ecVoltage = ecArrayAverage(ecArray, ecArrayLenth) * 5000 / 1024;

  // Serial.print(millis() / 1000.0, 3);
  // Serial.print(" : ");
  // Serial.print("ecVoltage: ");
  // Serial.print(ecVoltage);
  // Serial.print(" temperature: ");
  // Serial.print(temperature);

  float tempCoefficient = 1.0 + 0.0185 * (temperature - 25.87);
  float coefficientVoltage = (float)ecVoltage / tempCoefficient;
  // Serial.print(" coefficientVoltage: ");
  // Serial.print(coefficientVoltage);

  if (coefficientVoltage < 150 || coefficientVoltage > 3300 )
  {
    //25^C 1413us/cm<-->about 216mv  if the voltage(compensate)<150,that is <1ms/cm,out of the range
    //>20ms/cm,out of the range
    Serial.println("Subject is not in measurable range of EC");
    ecValue = 0;
  }
  else
  {
    if (coefficientVoltage <= 448)
    {
      //1ms/cm<EC<=3ms/cm
      ecValue = 6.84 * coefficientVoltage - 64.32;
    }
    else if (coefficientVoltage <= 1457)
    {
      //3ms/cm<EC<=10ms/cm
      ecValue = 6.98 * coefficientVoltage - 127;
    }
    //10ms/cm<EC<20ms/cm
    else ecValue = 5.3 * coefficientVoltage + 2278;
    // Serial.print(" ecValue: ");
    // Serial.print(ecValue, 0);
    // Serial.println("us/cm");
  }
  return ecValue;
}



// Calculate the average value of array
double macs_ec::ecArrayAverage(int* inputArray, int arrayLength) {
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


