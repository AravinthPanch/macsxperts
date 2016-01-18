#include <UC1701.h>
static const byte glyph[] = { B00010000, B00110100, B00110000, B00110100, B00010000 };
static UC1701 lcd;

const int backlightPin = 26;

void setup() {
  // PCD8544-compatible displays may have a different resolution...
  lcd.begin();
  // Add the smiley to position "0" of the ASCII table...
  lcd.createChar(0, glyph);
  pinMode(backlightPin, OUTPUT);
  digitalWrite (backlightPin, 0);
}


void loop() {
  // Just to show the program is alive...
  static int counter = 0;

  // Write a piece of text on the first line...
  lcd.setCursor(0, 0);
  lcd.print("Hello Macsxperts");

  // Write the counter on the second line...
  lcd.setCursor(0, 1);
  lcd.print(counter, DEC);
  lcd.write(' ');
  lcd.write(0);  // write the smiley

  delay(500);
  counter++;
}
