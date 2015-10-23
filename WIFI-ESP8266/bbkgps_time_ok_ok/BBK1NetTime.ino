//-------------------------------------------------------------------------
char netLink_bbkgps[38] = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
char cmdHttp_bbkgps[86] = "GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
//-------------------------------------------------------------------------
void NetLink_bbkgps_time() {
  HttpGetPost(netLink_bbkgps, cmdHttp_bbkgps, 5);
  smartDelay(10000);
}
//-------------------------------------------------------------------------
void BBKNetTimeExp(char c) {}
//-------------------------------------------------------------------------
void NetExp_bbkgps_show() {
  //lgln(F("----------------------"));
  //lgln(bufferBack);
  lgln(F("----------------------"));
  lgln(GetStringAB(bufferBack, F("Time="), F(";")));
  lgln(GetStringAB(bufferBack, F("Nows="), F(";")));
  lgln(GetStringAB(bufferBack, F("pm25="), F(";")));
  lgln(GetStringAB(bufferBack, F("days="), F(";")));
  lgln(F("----------------------"));
}
//-------------------------------------------------------------------------
