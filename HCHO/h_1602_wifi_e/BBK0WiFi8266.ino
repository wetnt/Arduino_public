//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
void netStart() {
  wfs.println(F("AT"));           smartDelayW(2000);
  wfs.println(F("AT+CWJAP?"));    smartDelayW(2000);//SeeAP
  wfs.println(F("AT+CIFSR"));     smartDelayW(2000);//seesIP
  wfs.println(F("AT+CWMODE=1"));  smartDelayW(2000);//beWiFi
}
void netJoinAP(String s, String p) {
  wfs.println(F("AT+CWMODE=1"));  smartDelayW(2000);//beWiFi
  wfs.println(F("AT+RST"));       smartDelayW(5000);//reBoot
  wfs.println("AT+CWJAP=\"" + s + "\",\"" + p + "\""); smartDelayW(10000);
  wfs.println(F("AT+CWJAP?"));    smartDelayW(2000);//SeeAP
  wfs.println(F("AT+CIFSR"));     smartDelayW(2000);//seesIP
}
//-------------------------------------------------------------------------
void HttpGetPost(String link, String text, int seconds) {
  wfs.println(link);
  smartDelayW(2000);
  wfs.println( "AT+CIPSEND=" + String(text.length() + 2) );
  smartDelayW(1000);
  wfs.println(text);
  smartDelayW(seconds * 1000);
}
//-------------------------------------------------------------------------
void NetLinkTestBaidu() {
  HttpGetPost(F("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80"), F("GET / HTTP/1.0\r\n\r\n") , 5); smartDelayW(1000);
}
//-------------------------------------------------------------------------
