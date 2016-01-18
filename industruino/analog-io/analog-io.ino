#include <Indio.h>
#include <Wire.h>

float sensorVal1;

void setup()
{
  Serial.begin(9600);
  Indio.setADCResolution(16);
  Indio.analogReadMode(1, mA);
}

void loop()
{
  sensorVal1 = Indio.analogRead(1);
  Serial.println(sensorVal1);
}

