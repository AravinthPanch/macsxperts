/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 25/01/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: DFRobot Analog EC Meter DFR0300
*/

// Libraries
#include "Arduino.h"

// Declarations
#define ecSensorPin A1
#define ecArrayLenth 20

class macs_ec
{
  private:
    int ecArray[ecArrayLenth];
    int ecArrayIndex = 0;
    double ecArrayAverage(int* arr, int arrayLength);

  public:
    float getEc(float temperature);
};
