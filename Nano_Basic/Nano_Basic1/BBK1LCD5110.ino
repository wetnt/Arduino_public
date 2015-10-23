//===================================================================
#include <PCD8544.h>
static PCD8544 lcd = PCD8544(A1, A2, A3, A4, A5);
//PCD8544(clock,data-in,data select,reset,enable);
//===================================================================
// A custom glyph (a smiley)...
static const byte glyph[] = { B00010000, B00110100, B00110000, B00110100, B00010000 };
//===================================================================
void LCD5110_setup() {
  lcd.begin(84, 48);
  lcd.setContrast(50);
  lcd.createChar(0, glyph);
}
void LCD5110_test() {
  // Just to show the program is alive...
  static int counter = 0;

  // Write a piece of text on the first line...
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");

  // Write the counter on the second line...
  lcd.setCursor(0, 1);
  lcd.print(counter, DEC);
  lcd.write(' ');
  lcd.write(0);  // write the smiley

  delay(200);
  counter++;
}


/* EOF - HelloWorld.ino */
