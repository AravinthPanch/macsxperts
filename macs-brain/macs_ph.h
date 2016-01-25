/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 18/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: DF Robot pH Pro
*/

// Libraries
#include "Arduino.h"

// Declarations
#define phArrayLenth 60
//pH meter Analog output to Arduino Analog Input 0
#define phSensorPin A0
//deviation compensate
#define phOffset 0.00

class macs_ph
{
  private:
    int counter = 0;
    int phArray[phArrayLenth];
    int phArrayIndex = 0;
    double phArrayAverage(int* arr, int arrayLength);

  public:
    int holaPh();
    float getPh();
};
