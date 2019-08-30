String TimeUpOk = "Up Err";
void WIFI_TIME_EXP(String t) {
  //Date: Mon, 12 Feb 2018 11:24:56 GMT
  String x = GetStringAB(t + "GMT", "2019 ", " GMT"); lg(x);
  if (x.length() == 8) {
    dt.time_by_string(x, 8);
    M5_RTC_Set();
    TimeUpOk = "UpK";
  } else {
    TimeUpOk = "UpE";
  }
}
void WIFI_TIME_Bad() {
  TimeUpOk = "UpE";
}
void WIFI_TIME_SHOW() {
  //lgln("-----------------------------------");
  lgln(dt.time_sting);
  //--------------------------------------------------
  //M5.Lcd.fillScreen(BLACK);
  M5.Rtc.GetBm8563Time(); RTC_DateTypeDef RTC_DateStruct; M5.Rtc.GetData(&RTC_DateStruct);
  float ppp = (pressure - 101325.0) * 100 / 101325.0;
  //--------------------------------------------------
  M5.Lcd.setCursor(  0,  0, 2);  M5.Lcd.printf("%04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
  M5.Lcd.setCursor( 86,  0, 2);  M5.Lcd.printf("%4.2fv ", vBatt);
  M5.Lcd.setCursor(130,  0, 2);  M5.Lcd.println(TimeUpOk);
  M5.Lcd.setCursor( 20, 24, 4);  M5.Lcd.printf("%02d:%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
  M5.Lcd.setCursor(  0, 56, 2);  M5.Lcd.printf("%2.1fC %2.0f%% %2.2f%%", tmp, hum, ppp);
  int tph = heading - 90; if (tph < 0) tph += 360;
  M5.Lcd.setCursor(124, 56, 2);  M5.Lcd.printf("^%03d\n", tph);
  //--------------------------------------------------
  BMM150_North_Line();
  //--------------------------------------------------
  //M5.Lcd.setCursor(100,  0, 2);  M5.Lcd.println(WiFi.SSID(0));
  //int bt = M5.getBatteryLevel();
  //--------------------------------------------------
  //M5.Lcd.setCursor( 0, 28, 2);  M5.Lcd.println(dt.time_sting);
  //M5.Lcd.setCursor( 0, 42, 2);  M5.Lcd.printf("P: %3.4f",ppp);
  //M5.Lcd.setCursor( 0, 56, 2);  M5.Lcd.printf("T: %2.1fC H: %2.0f%% P: %2.0f", tmp, hum, pressure);
  //--------------------------------------------------
}
void M5_RTC_Set() {
  M5.Lcd.setCursor(0, 0, 2);  M5.Lcd.println("M5 RTC SET");
  RTC_TimeTypeDef TimeStruct;
  TimeStruct.Hours   = dt.th;
  TimeStruct.Minutes = dt.tm;
  TimeStruct.Seconds = dt.ts + 1;
  M5.Rtc.SetTime(&TimeStruct);

  //  RTC_DateTypeDef DateStruct;
  //  DateStruct.WeekDay = 3;
  //  DateStruct.Month = 3;
  //  DateStruct.Date = 22;
  //  DateStruct.Year = 2019;
  //  M5.Rtc.SetData(&DateStruct);
}
