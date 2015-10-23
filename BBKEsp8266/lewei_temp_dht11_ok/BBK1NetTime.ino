//-------------------------------------------------------------------------
String netLink_bbkgps = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
String cmdHttp_bbkgps = "GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
//-------------------------------------------------------------------------
void NetLink_bbkgps_time() {
  HttpGetPost(netLink_bbkgps, cmdHttp_bbkgps, 5);
  smartDelay(10000);
}
//-------------------------------------------------------------------------
