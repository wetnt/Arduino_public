boolean TimeShowKey = true;
void WIFI_TIME_SHOW() {
  //lgln("-----------------------------------");
  lgln(dt.time_sting);
  //--------------------------------------------------
  if (TimeShowKey) {
    //--------------------------------------------------
    M5.Lcd.setRotation(3);
    //--------------------------------------------------
    M5.Rtc.GetBm8563Time(); RTC_DateTypeDef RTC_DateStruct; M5.Rtc.GetData(&RTC_DateStruct);
    float ppp = (pressure - 101325.0) * 100 / 101325.0;
    //--------------------------------------------------
    M5.Lcd.setCursor(  0,  0, 2);  M5.Lcd.printf("%04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
    M5.Lcd.setCursor( 82,  0, 2);  M5.Lcd.printf("%4.2fv ", vBat);
    //M5.Lcd.setCursor(124,  0, 2);  M5.Lcd.printf("%02dmA",oBat);
    M5.Lcd.setCursor(124,  0, 2);  M5.Lcd.printf("%.0f%%  ",cBat * 100);    
    //--------------------------------------------------
    M5.Lcd.setCursor( 20, 24, 4);  M5.Lcd.printf("%02d:%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
    M5.Lcd.setCursor(  0, 56, 2);  M5.Lcd.printf("%2.1fC %2.0f%% %2.2f%%", tmp, hum, ppp);
    //--------------------------------------------------
    int tph = heading - 90; if (tph < 0) tph += 360;
    M5.Lcd.setCursor(124, 56, 2);  M5.Lcd.printf("^%03d\n",  tph);
    BMM150_North_Line();
    //--------------------------------------------------
  } else {
    M5.Lcd.setRotation(0);
    Battery_Lcd();
  }
}
void TimeShowKey_turn() {
  TimeShowKey = !TimeShowKey;
}
