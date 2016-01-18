#include <Indio.h>
#include <Wire.h>
#include <UC1701.h>
static UC1701 lcd;

const int backlightPin = 26;

void setup()
{
  lcd.begin();
  pinMode(backlightPin, OUTPUT);
  digitalWrite (backlightPin, 0);

  Indio.digitalMode(1, OUTPUT);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Macsxperts Aeroponics");

  Indio.digitalWrite(1, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("HIGH");
  delay(2000);

  Indio.digitalWrite(1, LOW);
  lcd.clearLine();
  lcd.print("LOW");
  delay(2000);
}

