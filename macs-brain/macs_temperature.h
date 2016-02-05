/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 05/02/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: Temperature Sensor DS18B20 
*/

// Libraries
#include "Arduino.h"
#include <OneWire.h>   

// Declarations
#define temperatureSensorPin 47

class macs_temperature
{
  private:
    

  public:
  	macs_temperature();
  	float getTemperature();  
};
