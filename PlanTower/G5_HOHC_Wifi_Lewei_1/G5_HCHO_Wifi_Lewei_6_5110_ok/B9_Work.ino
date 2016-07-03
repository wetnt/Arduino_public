//=====================================================
void Work_Loop() {
  if ( ts_loop(60) ) Lewei_WorkRest();
  if ( ts_loop(1)  ) {
    LCD_Show_All(); //LG_Show_All();
  }
  if ( ts_loop(5)  ) {
    HCHO_Ask(); Si7021_read();
  }
}
//=====================================================
int LeweiTimes = 0;
void Lewei_WorkRest() {
  LeweiTimes++;
  if (LeweiTimes > 20) {
    LeweiTimes = 0; netReBoot();
  }
  Lewei_Loop();
}
void LCD_Show_All() {
  //lcd.clear();
  lcd.setCursor(0, 0);//lcd.print("T=");
  lcd.print(Si_Temperature); lcd.print(F("C  ")); lcd.print(Si_Humidity); lcd.print(F("%"));
  lcd.setCursor(0, 1); lcd.print(F("pm10 ")); lcd.print(g.cf10); lcd.print(F(" ug/m3\t"));
  lcd.setCursor(0, 2); lcd.print(F("pm25 ")); lcd.print(g.cf25); lcd.print(F(" ug/m3\t"));
  lcd.setCursor(0, 3); lcd.print(F("pm1X ")); lcd.print(g.cf1X); lcd.print(F(" ug/m3\t"));
  lcd.setCursor(0, 4); lcd.print(F("HCHO ")); lcd.print(fHCHO); lcd.print(" "); lcd.print(fHCHOavr);
  lcd.setCursor(0, 5); lcd.print(Lewei_Loop_N); lcd.print(Lewei_Time); //lcd.clearLine(); lcd.print(F(" "));
}
void LG_Show_All() {
  lg(Si_Temperature); lg(F("C  ")); lg(Si_Humidity); lg(F("%"));
  lg(F(" ")); lg(F("pm10 ")); lg(g.cf10); lg(F(" ug/m3\t"));
  lg(F(" ")); lg(F("pm25 ")); lg(g.cf25); lg(F(" ug/m3\t"));
  lg(F(" ")); lg(F("pm1X ")); lg(g.cf1X); lg(F(" ug/m3\t"));
  lg(F(" ")); lg(F("HCHO ")); lg(fHCHO); lg(" "); lg(fHCHOavr);
  lg(F(" ")); lg(Lewei_Loop_N); lg(Lewei_Time); lg();
}
//=====================================================
