#include "PCD8544.h"
static PCD8544 lcd;//PCD8544(clock,data-in,data select,reset,enable);
//52,50,48,46,44
//SC,RST,DC,DN,CLK
void LCD5110_setup() {
  lgln(F("LCD5110_setup..."));
  lcd=PCD8544(44,46,48,50,52);//(clock,data-in,data select,reset,enable);  
  lcd.begin(84, 48);
  lcd.setContrast(48);
  lcd.setCursor(0, 0);
  LCD_Show_BOBOKing();
}
void LCD_Show_BOBOKing() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(F("  BOBOKing.COM")); 
  lcd.setCursor(0, 2); lcd.print(F(" Temperature..."));
  lcd.setCursor(0, 3); lcd.print(F(" Humidity..."));
  lcd.setCursor(0, 4); lcd.print(F(" PM2.5 info..."));
  lcd.setCursor(0, 5); lcd.print(F(" HCHO  info..."));
  delay(5000);
  lcd.clear();
}
void LCD5110_loop() {
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
