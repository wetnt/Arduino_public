//-------------------------------------------------------------------------
void NetLink_bbkgps_time() {
  HttpGetPost(
    F("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80"),
    F("GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n")
    , 5
  );
  smartDelay(1000);
}
//-------------------------------------------------------------------------
void BBKNetTimeExp(char c) {}
//-------------------------------------------------------------------------
String t = "";
void NetExp_bbkgps_show() {
  //-------------------------------------------------------------------------
  //lgln(F("----------------------"));
  //GpuClear();
  t = GetStringAB(bufferBack, F("Time="), F(";")); t.replace("ime", ""); GpuShow(0,  0, t , 2, false);
  t = GetStringAB(bufferBack, F("Nows="), F(";")); t.replace("ows", ""); GpuShow(0, 32, t , 2, false);
  t = GetStringAB(bufferBack, F("pm25="), F(";")); t.replace("m25", ""); GpuShow(0, 64, t , 2, false);
  t = GetStringAB(bufferBack, F("days="), F(";")); t.replace("ays", ""); GpuShow(0, 96, t , 2, false);
  t = GetStringAB(bufferBack, F("skys="), F(";")); t.replace("kys", ""); GpuShow(0, 128, t , 2, false);
  t = GetStringAB(bufferBack, F("temp="), F(";")); t.replace("emp", ""); GpuShow(0, 160, t , 2, false);
  t = GetStringAB(bufferBack, F("wind="), F(";")); t.replace("ind", ""); GpuShow(0, 192, t , 2, true);
  //lgln(F("----------------------"));
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
