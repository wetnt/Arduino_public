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
String jionAP = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(pass) + "\"";
//-------------------------------------------------------------------------
char prSend[12] = "AT+CIPSEND=";
//-------------------------------------------------------------------------
char netLink[38] = "AT+CIPSTART=\"TCP\",\"www.baidu.com\",80";
char cmdHttp[20] = "GET / HTTP/1.0\r\n\r\n";
//=========================================================================
void netStart() {
  wfs.println(testAT); smartDelay(2000);
  wfs.println(seesAP); smartDelay(2000);
  wfs.println(seesIP); smartDelay(2000);
  wfs.println(beWiFi); smartDelay(2000);
}
void netJoinAP(String s, String p) {
  jionAP = "AT+CWJAP=\"" + s + "\",\"" + p + "\"";
  wfs.println(jionAP); smartDelay(10000);
}
//-------------------------------------------------------------------------
void HttpGetPost(String link, String text, int seconds) {
  int n = text.length() + 2;
  wfs.println(link); smartDelay(4000);
  wfs.println(prSend + String(n));    smartDelay(1000);
  wfs.println(text); HttpBufferClear(); smartDelay(seconds * 1000);
}
//-------------------------------------------------------------------------
String bufferBack; bool bufferKeys = false;
void HttpBufferClear() {
  bufferBack = "";  //bufferKeys = true;
}
void HttpBufferSave(char c) {
  if (c == 'T') {
    HttpBufferClear(); bufferKeys = true; bufferBack += c;
  } else {
    if (bufferKeys) { bufferBack += c; }
  }
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void NetLinkTestBaidu() {
  HttpGetPost(netLink, cmdHttp, 5); smartDelay(10000);
}
//-------------------------------------------------------------------------
