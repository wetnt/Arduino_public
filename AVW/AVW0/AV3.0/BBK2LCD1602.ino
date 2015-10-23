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

