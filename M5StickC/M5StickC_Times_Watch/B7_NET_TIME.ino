//--------------------------------------------------
boolean TimeShowKey = true;
void TimeShowKey_turn() {
  TimeShowKey = !TimeShowKey;
}
void WIFI_TIME_SHOW() {
  //lgln("-----------------------------------");
  //lgln(dt.time_sting);
  //--------------------------------------------------
  if (TimeShowKey) {
    //--------------------------------------------------
    M5.Lcd.setRotation(3);
    //--------------------------------------------------
    M5.Rtc.GetBm8563Time(); RTC_DateTypeDef RTC_DateStruct; M5.Rtc.GetData(&RTC_DateStruct);
    //--------------------------------------------------
    M5.Lcd.setCursor(  0,  0, 2);  M5.Lcd.printf("%04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
    M5.Lcd.setCursor( 82,  0, 2);  M5.Lcd.printf("%4.2fv ", vBat);
    M5.Lcd.setCursor(130,  0, 2);  M5.Lcd.printf("%.0f%%  ", cBat * 100);
    //--------------------------------------------------
    M5.Lcd.setCursor( 20, 24, 4);  M5.Lcd.printf("%02d:%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
    M5.Lcd.setCursor(  0, 60, 2);  M5.Lcd.printf("B %.0fmW %.0fmA  U %.0fmA    ", pBat, oBat, iUSB);
    //--------------------------------------------------
  } else {
    M5.Lcd.setRotation(0);
    Battery_Lcd();
  }
}
void M5_RTC_Set() {
  //M5.Lcd.setCursor(0, 0, 2);M5.Lcd.println("M5 RTC SET");
  RTC_TimeTypeDef TimeStruct;
  TimeStruct.Hours   = dt.th;
  TimeStruct.Minutes = dt.tm;
  TimeStruct.Seconds = dt.ts + 1;
  M5.Rtc.SetTime(&TimeStruct);
}
