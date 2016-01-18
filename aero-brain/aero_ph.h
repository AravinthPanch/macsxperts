/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 18/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: DF Robot pH Pro
*/

// Third party Libraries
#include "Print.h"


#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define samplingInterval 20
#define ArrayLenth  40    //times of collection

class aero_ph
{
  private:
    int counter = 0;    
    int pHArray[ArrayLenth];   
    int pHArrayIndex = 0;
    double avergearray(int* arr, int number);
    Print* Serial;

  public:
    aero_ph(Print* _serial);    
    int holaPh();
    float getPh();
};
