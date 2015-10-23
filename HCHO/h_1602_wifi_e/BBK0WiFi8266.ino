//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
char ssid[5] = "MMMM";
char pass[14] = "1234567890123";
boolean backKey = false;
//-------------------------------------------------------------------------
char testAT[3] = "AT";
char beWiFi[12] = "AT+CWMODE=1";
char reStar[7] = "AT+RST";
char seesAP[10] = "AT+CWJAP?";
char seesIP[9] = "AT+CIFSR";
//-------------------------------------------------------------------------
char prSend[12] = "AT+CIPSEND=";
//-------------------------------------------------------------------------
char netLink[38] = "AT+CIPSTART=\"TCP\",\"www.baidu.com\",80";
char cmdHttp[20] = "GET / HTTP/1.0\r\n\r\n";
//=========================================================================
void netStart() {
  wfs.println(testAT); smartDelayW(2000);
  wfs.println(beWiFi); smartDelayW(2000);
  wfs.println(reStar); smartDelayW(2000);
  wfs.println(seesAP); smartDelayW(2000);
  wfs.println(seesIP); smartDelayW(2000);
}
void netJoinAP(String s, String p) {
  wfs.println(testAT); smartDelayW(2000);
  wfs.println("AT+CWJAP=\"" + s + "\",\"" + p + "\""); smartDelayW(20000);
  wfs.println(seesAP); smartDelayW(2000);
  wfs.println(seesIP); smartDelayW(2000);
}
//-------------------------------------------------------------------------
void HttpGetPost(String link, String text, int seconds) {
  int n = text.length() + 2;
  wfs.println(link); smartDelayW(4000);
  wfs.println(prSend + String(n));  smartDelayW(1000);
  wfs.println(text);                smartDelayW(seconds * 1000);
}
//-------------------------------------------------------------------------
void NetLinkTestBaidu() {
  HttpGetPost(netLink, cmdHttp, 5); smartDelayW(10000);
}
//-------------------------------------------------------------------------
