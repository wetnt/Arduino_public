//-------------------------------------------------------------------------
char netLink_bbkgps[38] = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
char cmdHttp_bbkgps[86] = "GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
//-------------------------------------------------------------------------
void NetLink_bbkgps_time() {
  HttpGetPost(netLink_bbkgps, cmdHttp_bbkgps, 5); smartDelay(1000);
}
//-------------------------------------------------------------------------
void BBKNetTimeExp(char c) {}
//-------------------------------------------------------------------------
String t = "";
void NetExp_bbkgps_show() {
  //-------------------------------------------------------------------------
  //lgln(F("----------------------"));
  //GpuClear();
  t = GetStringAB(bufferBack, F("Time="), F(";")); GpuShow(0,  0, t , 2);
  t = GetStringAB(bufferBack, F("Nows="), F(";")); GpuShow(0, 32, t , 2);
  t = GetStringAB(bufferBack, F("pm25="), F(";")); GpuShow(0, 64, t , 2);
  t = GetStringAB(bufferBack, F("days="), F(";")); GpuShow(0, 96, t , 2);
  t = GetStringAB(bufferBack, F("skys="), F(";")); GpuShow(0, 128, t , 2);
  t = GetStringAB(bufferBack, F("temp="), F(";")); GpuShow(0, 160, t , 2);
  t = GetStringAB(bufferBack, F("wind="), F(";")); GpuShow(0, 192, t , 2);
  lgln();
  //lgln(F("----------------------"));
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
