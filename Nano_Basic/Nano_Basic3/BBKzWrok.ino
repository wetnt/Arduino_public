//===================================================================
void Timer_work() {
  //-------------------------------------
  int timerEvent3 = timerLoop.every(1000, GPS_work) ; //GPS状态输出
  //int timerEvent4 = timerLoop.every(1000, WorkRunA) ; //状态呼吸灯
  //-------------------------------------
}
//===================================================================
void GPS_work() {
  GpsValueSet();
  GpsStringSet();
  GpsLineShow();
  GPS_LCD5110_Show();
}
void GPS_LCD5110_Show() {
  //-------------------------------------------------------------------------------
  lcd.setCursor(0, 0);  lcd.print("BOBOKing.GPS.!");
  //-------------------------------------------------------------------------------
  lcd.setCursor(0, 1);  lcd.print(gs.ds);
  lcd.setCursor(36, 1);  lcd.print(gs.t);
  //-------------------------------------------------------------------------------
  lcd.setCursor(0, 2);  lcd.print(gs.k);
  lcd.setCursor(6, 2);  lcd.print(gs.p);
  lcd.setCursor(18,2);  lcd.print("N"); lcd.setCursor(24, 2);  lcd.print(gs.n);
  lcd.setCursor(48,2);  lcd.print("R"); lcd.setCursor(54, 2);  lcd.print(gs.r);
  //-------------------------------------------------------------------------------
  lcd.setCursor(0, 3);  lcd.print("W:"); lcd.setCursor(24, 3);  lcd.print(gs.w);
  lcd.setCursor(0, 4);  lcd.print("J:"); lcd.setCursor(18, 4);  lcd.print(gs.j);
  //-------------------------------------------------------------------------------
  lcd.setCursor(0, 5);  lcd.print("H:"); lcd.setCursor(12, 5);  lcd.print(gs.h);
  lcd.setCursor(42,5);  lcd.print("V:"); lcd.setCursor(60, 5);  lcd.print(gs.v);
  //lcd.setCursor(0, 5);  lcd.print("w:"); lcd.setCursor(42,5);  lcd.print(gs.x);
  //-------------------------------------------------------------------------------
}
//===================================================================
bool LightKey = false;
void WorkRunA() {
  LightKey = !LightKey;
  if (LightKey) {
    digitalWrite(13, HIGH);  lgs.println("HIGH");  //delay(1000);
  } else {
    digitalWrite(13, LOW);   lgs.println("LOW");   //delay(1000);
  }
}
//===================================================================
