/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 18/01/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: DFRobot pH Pro (SEN0169)
*/
// Libraries
#include "Arduino.h"

// Declarations
#define phSensorPin A0
#define phArrayLenth 60
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
