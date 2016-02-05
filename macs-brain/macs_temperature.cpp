/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 05/02/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: Temperature Sensor DS18B20 using Dallas OneWire
*/

// Libraries
#include "macs_temperature.h"

OneWire oneWireBus(temperatureSensorPin);

// Constructor
macs_temperature::macs_temperature() {
}

//returns the temperature from one DS18B20 in DEG Celsius
float macs_temperature::getTemperature() {

 byte data[12];
 byte addr[8];

 if ( !oneWireBus.search(addr)) {
   //no more sensors on chain, reset search
   oneWireBus.reset_search();
   return -1000;
 }

 if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }

 oneWireBus.reset();
 oneWireBus.select(addr);
 // start conversion, with parasite power on at the end
 oneWireBus.write(0x44, 1);

 byte present = oneWireBus.reset();
 oneWireBus.select(addr);
 // Read Scratchpad
 oneWireBus.write(0xBE);


 // we need 9 bytes
 for (int i = 0; i < 9; i++) {
   data[i] = oneWireBus.read();
 }

 oneWireBus.reset_search();

 byte MSB = data[1];
 byte LSB = data[0];

 //using two's compliment
 float tempRead = ((MSB << 8) | LSB);
 float TemperatureSum = tempRead / 16;

 return TemperatureSum;
}
