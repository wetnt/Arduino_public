void WIFI_TIME_EXP(String t) {
  //Date: Mon, 12 Feb 2018 11:24:56 GMT
  String x = GetStringAB(t + "GMT", "2018 ", " GMT"); lg(x);
  dt.time_by_string(x, 8);
}
void WIFI_TIME_SHOW() {
  oled.clear();
  oled.setFont(ArialMT_Plain_24);
  oled.drawString(20, 0, dt.time_sting);
  oled.drawString(0,25,"Temp:");
  oled.drawString(70,25,String(WDLD));
  oled.display();
}

