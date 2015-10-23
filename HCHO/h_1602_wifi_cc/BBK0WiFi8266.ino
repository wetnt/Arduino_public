//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
const char testAT[3] = "AT";
const char beWiFi[12] = "AT+CWMODE=1";
const char reStar[7] = "AT+RST";
const char seesAP[10] = "AT+CWJAP?";
const char seesIP[9] = "AT+CIFSR";
//-------------------------------------------------------------------------
const char prSend[12] = "AT+CIPSEND=";
//-------------------------------------------------------------------------
const char netLink[38] = "AT+CIPSTART=\"TCP\",\"www.baidu.com\",80";
const char cmdHttp[20] = "GET / HTTP/1.0\r\n\r\n";
//=========================================================================
void netStart() {
  wfs.println(testAT); smartDelay(2000);
  //wfs.println(beWiFi); smartDelay(2000);
  //wfs.println(reStar); smartDelay(10000);
  //wfs.println(seesAP); smartDelay(2000);
  //wfs.println(seesIP); smartDelay(2000);
}
void netJoinAP(String s, String p) {
  wfs.println("AT+CWJAP=\"" + s + "\",\"" + p + "\"");
  smartDelay(10000);
}
//-------------------------------------------------------------------------
void HttpGetPost(String link, String text, int seconds) {
  int n = text.length() + 2;
  wfs.println(link); smartDelay(4000);
  wfs.println(prSend + String(n));  smartDelay(1000);
  wfs.println(text);                smartDelay(seconds * 1000);
}
//-------------------------------------------------------------------------
void NetLinkTestBaidu() {
  HttpGetPost(netLink, cmdHttp, 5); smartDelay(10000);
}
//-------------------------------------------------------------------------
