//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
String ssid = "MMMM";
String pass = "1234567890123";
boolean backKey = false;
//-------------------------------------------------------------------------
String testAT = "AT";
String jionAP = "AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"";
String seesAP = "AT+CWJAP?";
String seesIP = "AT+CIFSR";
String reStar = "AT+RST";
String beWiFi = "AT+CWMODE=1";
//-------------------------------------------------------------------------
String prSend = "AT+CIPSEND=";
//-------------------------------------------------------------------------
String netLink = "AT+CIPSTART=\"TCP\",\"www.baidu.com\",80";
String cmdHttp = "GET / HTTP/1.0\r\n\r\n";
//=========================================================================
void netStart() {
  wfs.println(testAT); smartDelay(2000);
  wfs.println(seesAP); smartDelay(2000);
  wfs.println(seesIP); smartDelay(2000);
  wfs.println(beWiFi); smartDelay(2000);
}
void netJoinAP(String s, String p) {
  jionAP = "AT+CWJAP=\"" + s + "\",\"" + p + "\"";
  wfs.println(jionAP); smartDelay(2000);
}
//-------------------------------------------------------------------------
void HttpGetPost(String link, String text, int seconds) {
  int n = text.length() + 2;
  wfs.println(link); smartDelay(4000);
  wfs.println(prSend + String(n));    smartDelay(1000);
  wfs.println(text); HttpBufferSet(); smartDelay(seconds * 1000);
}
//-------------------------------------------------------------------------
String bufferBack = "";
void HttpBufferSet() {
  bufferBack = "";
  bufferKey = true;
}
void HttpBufferSave(char c) {
  bufferBack += c;
}
//-------------------------------------------------------------------------
void NetLinkTestBaidu() {
  HttpGetPost(netLink, cmdHttp, 5); smartDelay(10000);
}
//-------------------------------------------------------------------------
