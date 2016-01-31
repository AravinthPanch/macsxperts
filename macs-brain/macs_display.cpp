/**
   Author: Aravinth Panchadcharam
   Email: me@aravinth.info
   Date: 24/01/16.
   Project: Macsxperts Aeroponics Vertical Farming
   Description: HD44780 16x2 LCD
*/
// Libraries
#include "macs_display.h"
#include <LiquidCrystal.h>


// Constructor
LiquidCrystal lcd(lcdRSpin, lcdENpin, lcdD4pin, lcdD5pin, lcdD6pin, lcdD7pin);

macs_display::macs_display() {
  lcd.begin(16, 2);
  showDefaults();
}

// Show defaults of the lcd display
void macs_display::showDefaults() {
  // First line to show PH value of 8 character long
  lcd.setCursor(0, 0);
  lcd.print("pH: ");

  // First line after ph to show EC
  lcd.setCursor(9, 0);
  lcd.print("EC: ");
};

// Show pH value in the lcd display
void macs_display::showPh(float val) {
  Serial.print(millis() / 1000.0, 3);
  Serial.print(" : ");
  Serial.print("ph: ");
  Serial.println(val);
  lcd.setCursor(4, 0);
  lcd.print(val, 2);
}

// Show EC value in the lcd display
void macs_display::showEc(float val) {
  lcd.setCursor(13, 0);
  lcd.print(val, 2);
}

// Show given message in the lcd display
void macs_display::showMsg(String msg) {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(msg);
}