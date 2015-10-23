//===============================================================
#include <LiquidCrystal.h>
//===============================================================
//LiquidCrystal(rs, enable,d0, d1, d2, d3,d4, d5, d6, d7);
//LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
//LiquidCrystal(rs, rw, enable, d0, d1, d2, d3);
//LiquidCrystal(rs, enable, d0, d1, d2, d3);
//LiquidCrystal lcd(7, 8, 9, 6, 5, 4, 3);
LiquidCrystal lcd(A0, A1, A2, 8, 7, 6, 5);
//===============================================================
void LCD_Setup(){
  //-----------------------------------
  lcd.begin(16, 2);
  lcd.print("BOBOKing LCD1602 ...");
  //-----------------------------------
}
void LCD_Loop(){
  //---------------------------------------
  lcd.clear();
  String sa = String("W=") + String(Watt) + String(" ") + String("K=") + String(Kwhs);
  String sb = String("V=") + String(Volt) + String(" ") + String("A=") + String(Amps);
  lcd.setCursor(0,0);   
  lcd.print(sa);
  lcd.setCursor(0,1);   
  lcd.print(sb);
  //---------------------------------------
}
//===============================================================

