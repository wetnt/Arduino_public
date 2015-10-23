LiquidCrystal lcd(7, 8, 9, 6, 5, 4, 3);

void BBKLcdInit(){
  //-----------------------------------
  lcd.begin(16, 2);
  lcd.print("BBKLCD1602");
  //-----------------------------------
}
void BBKLcdShow(){
  //---------------------------------------
  lcd.clear();
  String sa = String("V=") + String(Volt) + String(" ") + String("A=") + String(Amps);
  String sb = String("W=") + String(Watt) + String(" ") + String("K=") + String(Kwhs);
  lcd.setCursor(0,0); 
  lcd.print(sa);
  lcd.setCursor(0,1); 
  lcd.print(sb);
  //---------------------------------------
}
