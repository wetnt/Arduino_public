//===============================================
long LCDTime = millis(), LCDTimeKey = 1000;
//------------------------------------------
void LCD_Loop(bool showkey) {
  //---------------------------------------
  if ( millis() - LCDTime < LCDTimeKey) return;
  LCDTime = millis();
  //---------------------------------------
  LCD_Show_AVW(showkey);
  //---------------------------------------
}
void LCD_Show_AVW(bool showkey) {
  //----------------------------------------------------------------------------------------------
  //String t = ""; //t.concat(thour); t.concat(":"); t.concat(tmint); t.concat(":"); t.concat(tsecd);
  // t.concat(' '); t.concat((int)DHT_WD); t.concat("c "); t.concat((int)DHT_SD); t.concat('%');
  //String a = ""; a.concat("W="); a.concat(Watt); a.concat(" "); a.concat("A="); a.concat(Watt);
  String t = RunTimeShow();
  String b = "";
  b.concat(Watt); b.concat(' ');
  b.concat(Amps); b.concat(' ');
  b.concat(Volt); b.concat(' ');
  b.concat(Kwhs);
  //----------------------------------------------------------------------------------------------
  lcd.clear();
  lcd.setCursor(0, 0);     lcd.print(t);
  lcd.setCursor(0, 1);     lcd.print(b);
  //----------------------------------------------------------------------------------------------
}
