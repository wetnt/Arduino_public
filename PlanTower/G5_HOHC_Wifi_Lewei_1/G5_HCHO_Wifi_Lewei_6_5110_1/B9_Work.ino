//=====================================================
int Work_Secend = 15; unsigned long Work_Time = millis();
void Work_Loop() {
  if (millis() - Work_Time < Work_Secend * 1000) return;
  Work_Time = millis(); Work_Loop_Run();
}
//=====================================================
void Work_Loop_Run() {
  Lewei_Loop();
}
//=====================================================
int Work_Secend_A = 1; unsigned long Work_Time_A = millis();
void Work_Loop_A() {
  if (millis() - Work_Time_A < Work_Secend_A * 1000) return;
  Work_Time_A = millis(); Work_Loop_Run_A();
}
//=====================================================
void Work_Loop_Run_A() {
  //lg(F("------------------------------------")); lg();
  //G5_Show(); ShowHCHO(); Si7021_show();lg();
  LCD_Show_All();
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
//=====================================================
