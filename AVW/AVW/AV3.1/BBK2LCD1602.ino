LiquidCrystal lcd(8,7,6,5,4,3,2);

void BBKLcd_Setup(){
  //-----------------------------------
  lcd.begin(16, 2);
  lcd.print("BBKLCD1602");
  //-----------------------------------
}
void BBKLcd_Loop(){
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

void LCD_Show(char *a,char *b) {
  //---------------------------------------
  lcd.clear();
  lcd.setCursor(0,0);   
  lcd.print(a);
  lcd.setCursor(0,1);   
  lcd.print(b);
  //---------------------------------------
}
char lcd_a[17], lcd_b[17];
char floatString[4];
void LCD_AVW_Show(){
  //---------------------------------------
  dtostrf(Amps, 4, 1, floatString);
  //snprintf(lcd_a, 16, "Time: %02d:%02d:%02d", time_hourss,time_minute,time_second);
  snprintf(lcd_a, 16, "W= %d A= %s", Watt,floatString);
  snprintf(lcd_b, 18, "V= %d K= %d", Volt,Kwhs);
  LCD_Show(lcd_a,lcd_b);
  //---------------------------------------
}

