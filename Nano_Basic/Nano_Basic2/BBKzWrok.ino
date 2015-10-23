//===================================================================
void Timer_work() {
  //-------------------------------------
  int timerEvent3 = timerLoop.every(1000, GPS_work) ; //GPS状态输出
  int timerEvent4 = timerLoop.every(1000, WorkRunA) ; //状态呼吸灯
  //-------------------------------------
}
//===================================================================
void GPS_work() {
  GpsValueSet();
  GpsStringSet();
  GpsLineShow();

  lcd.setCursor(0, 0);  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);  lcd.print(gs.d);
  lcd.setCursor(0, 2);  lcd.print(gs.t);
  lcd.setCursor(0, 3);  lcd.print(gs.w);
  lcd.setCursor(0, 4);  lcd.print(gs.j);
  lcd.setCursor(0, 5);  lcd.print(gs.v);
  lcd.setCursor(40, 5);  lcd.print(gs.x);
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
