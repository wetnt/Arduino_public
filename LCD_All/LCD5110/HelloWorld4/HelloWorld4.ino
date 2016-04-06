#include "PCD8544.h"
static const byte glyph[] = { B00010000, B00110100, B00110000, B00110100, B00010000 };
static PCD8544 lcd;


//PCD8544(clock,data-in,data select,reset,enable);

//52,50,48,46,44
//SC,RST,DC,DN,CLK

void setup() {
  //lcd=PCD8544(6,5,4,3,2);//(clock,data-in,data select,reset,enable);
  lcd=PCD8544(44,46,48,50,52);//(clock,data-in,data select,reset,enable);  
  lcd.begin(84, 48);
  lcd.setContrast(49);
}


void loop() {
  static int counter = 0;

  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");

  lcd.setCursor(0, 1);
  lcd.print(counter, DEC);
  lcd.write(' ');
  lcd.write(0);

  delay(200);
  counter++;
}


/* EOF - HelloWorld.ino */
