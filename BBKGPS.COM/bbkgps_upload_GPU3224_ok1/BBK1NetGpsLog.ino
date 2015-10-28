//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
String NetGpsLog(String n, String p, String w, String j, String h, String v, String x, String r, String t) {
  return
    String(F("/v/s.php")) +
    String(F("?n=")) + n + String(F("&p=")) + p + String(F("&g=")) +
    w + String(F(",")) + j + String(F(",")) + h + String(F(",")) +
    v + String(F(",")) + x + String(F(",")) + r + String(F(",")) +
    t + String(F(""));
}
void NetLink_bbkgps_log(String getUrl) {
  HttpGetPost(
    F("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80"),
    //String(F("GET /v/s.php?n=boboking&p=123xjp&g=23,118,8848,80,270,12,1446048000000 HTTP/1.1 \r\n")) +
    String(F("GET ")) + getUrl +  String(F(" HTTP/1.1 \r\n")) +
    String(F("Host: www.bbkgps.com \r\n")) +
    String(F("User-Agent: abc \r\nConnection: close \r\n\r\n"))
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
  //t = GetStringAB(bufferBack, F("Time="), F(";")); t.replace("ime", ""); GpuShow(0,  0, t , 2, false);
  //t = GetStringAB(bufferBack, F("Nows="), F(";")); t.replace("ows", ""); GpuShow(0, 32, t , 2, false);
  //t = GetStringAB(bufferBack, F("pm25="), F(";")); t.replace("m25", ""); GpuShow(0, 64, t , 2, false);
  //t = GetStringAB(bufferBack, F("days="), F(";")); t.replace("ays", ""); GpuShow(0, 96, t , 2, false);
  //t = GetStringAB(bufferBack, F("skys="), F(";")); t.replace("kys", ""); GpuShow(0, 128, t , 2, false);
  //t = GetStringAB(bufferBack, F("temp="), F(";")); t.replace("emp", ""); GpuShow(0, 160, t , 2, false);
  //t = GetStringAB(bufferBack, F("wind="), F(";")); t.replace("ind", ""); GpuShow(0, 192, t , 2, true);
  //lgln(F("----------------------"));
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
