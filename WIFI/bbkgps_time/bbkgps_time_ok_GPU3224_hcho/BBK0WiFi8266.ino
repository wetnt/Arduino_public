//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
char prSend[12] = "AT+CIPSEND=";
//=========================================================================
void netStart() {
  wfs.println(F("AT"));           smartDelay(2000);
  wfs.println(F("AT+CWJAP?"));    smartDelay(2000);//SeeAP
  wfs.println(F("AT+CIFSR"));     smartDelay(2000);//seesIP
  wfs.println(F("AT+CWMODE=1"));  smartDelay(2000);//beWiFi
}
void netJoinAP(String s, String p) {
  wfs.println(F("AT"));           smartDelay(2000);
  wfs.println(F("AT+CWMODE=1"));  smartDelay(2000);//beWiFi
  wfs.println(F("AT+RST"));       smartDelay(5000);//reBoot  
  wfs.println("AT+CWJAP=\"" + s + "\",\"" + p + "\""); smartDelay(10000);
  wfs.println(F("AT+CWJAP?"));    smartDelay(2000);//SeeAP
  wfs.println(F("AT+CIFSR"));     smartDelay(2000);//seesIP
}
//-------------------------------------------------------------------------
void HttpGetPost(String link, String text, int seconds) {
  int n = text.length() + 2;
  wfs.println(link); smartDelay(2000);
  wfs.println(prSend + String(n));      smartDelay(1000);
  wfs.println(text); HttpBufferClear(); smartDelay(seconds * 1000);
}
//-------------------------------------------------------------------------
String bufferBack; bool bufferKeys = false;
void HttpBufferClear() {
  bufferBack = "";  //bufferKeys = true;
}
void HttpBufferSave(char c) {
  if (c == '$' ) {
    HttpBufferClear(); bufferKeys = true; bufferBack += c;
  } else if (c == '*' ) {
    bufferKeys = false;
  } else {
    if (bufferKeys) bufferBack += c;
  }
}
//-------------------------------------------------------------------------
void NetLinkTestBaidu() {
  HttpGetPost(F("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80"),F("GET / HTTP/1.0\r\n\r\n") , 5); smartDelay(1000);
}
//-------------------------------------------------------------------------
