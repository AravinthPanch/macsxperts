/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 24/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: HD44780 16x2 LCD
*/

// Libraries
#include "Arduino.h"

// Declarations
#define lcdD4pin 37
#define lcdD5pin 35
#define lcdD6pin 33
#define lcdD7pin 31
#define lcdRSpin 29
#define lcdENpin 27

class macs_display
{
  private:

  public:
    macs_display();
    void showDefaults();
    void showPh(float val);
    void showEc(float val);
    void showMsg(String msg);
};
