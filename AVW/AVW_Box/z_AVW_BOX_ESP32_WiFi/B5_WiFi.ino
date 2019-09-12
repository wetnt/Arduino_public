//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
#include <SoftwareSerial.h>
SoftwareSerial wfs(9, 12); // RX, TX
//SoftwareSerial wfs(10, 11); // RX, TX
//SoftwareSerial wfs(8, 9); // RX, TX
static const long GasBaud = 9600;
boolean lgShowKey = false;
//=========================================================================
void wifi_Init(boolean lgKey) {
  lgShowKey = lgKey;
  wfs.begin(GasBaud); lg(F("WiFi.Serial.start! = ")); lg(GasBaud); lg();
  //netStart();
  //netJoinAP(F("MMMM"),F("1234567890123"));
  //netJoinAP("acDev","AbroadCar2015()");
  //NetLinkTestBaidu();
}
void wfs_loop() {
  wfs.listen();
  while (wfs.available()) {
    char c = wfs.read();
    if (lgShowKey) lgs.write(c);
    HttpBufferSave(c);
  }
}
//=========================================================================
void netStart() {
  wfs.listen();
  wfs.println(F("AT"));           smartDelayWifi(100);
  wfs.println(F("AT+CWJAP?"));    smartDelayWifi(100);//SeeAP
  wfs.println(F("AT+CIFSR"));     smartDelayWifi(100);//seesIP
  wfs.println(F("AT+CWMODE=1"));  smartDelayWifi(100);//beWiFi
}
void netJoinAP(String s, String p) {
  wfs.listen();
  wfs.println(F("AT"));           smartDelayWifi(100);
  wfs.println(F("AT+CWMODE=1"));  smartDelayWifi(100);//beWiFi
  wfs.println(F("AT+RST"));       smartDelayWifi(3000);//reBoot
  wfs.println("AT+CWJAP=\"" + s + "\",\"" + p + "\""); smartDelayWifi(10*1000);
  wfs.println(F("AT+CWJAP?"));    smartDelayWifi(100);//SeeAP
  wfs.println(F("AT+CIFSR"));     smartDelayWifi(100);//seesIP
}
//-------------------------------------------------------------------------
void HttpGetPost(String link, String text, int seconds) {  
  int n = text.length() + 2;
  wfs.listen();
  wfs.println(link); smartDelayWifi(1000);
  wfs.print(F("AT+CIPSEND=")); wfs.println(n); smartDelayWifi(100);
  wfs.println(text);
  HttpBufferClear(); smartDelayWifi(seconds * 1000);
}
//=========================================================================
String bufferBack; bool bufferKeys = false;
char bufferStart = '+', bufferEnd = '}';
//-------------------------------------------------------------------------
void HttpBufferSet(char s, char e) {
  bufferStart = s; bufferEnd = e;
}
void HttpBufferClear() {
  bufferBack = "";  //bufferKeys = true;
}
void HttpBufferSave(char c) {
  if (c == bufferStart ) {
    HttpBufferClear(); bufferKeys = true; bufferBack += c;
  } else if (c == bufferEnd ) {
    bufferKeys = false;
  } else {
    if (bufferKeys) bufferBack += c;
  }
}
void HttpBufferShow() {
  lg(bufferBack);
}
//=========================================================================
void NetLinkTestBaidu() {
  HttpGetPost(F("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80"), F("GET / HTTP/1.0\r\n\r\n"), 5); smartDelayWifi(1000);
}
//=========================================================================
