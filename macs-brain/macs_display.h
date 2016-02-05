/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 24/01/16.
   Project: Macsxperts Vertical Farming Solutions
   Description: HD44780 16x2 LCD
*/

// Libraries
#include "Arduino.h"

// Declarations
#define lcdRSpin 29
#define lcdENpin 27
#define lcdD4pin 37
#define lcdD5pin 35
#define lcdD6pin 33
#define lcdD7pin 31

class macs_display
{
  private:

  public:
    macs_display();
    void showDefaults();
    void showPh(float val);
    void showEc(float val);
    void showTemperature(float val);
    void showMsg(String msg);
};
