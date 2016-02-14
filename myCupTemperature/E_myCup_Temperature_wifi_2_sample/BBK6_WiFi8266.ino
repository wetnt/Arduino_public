//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
#include <SoftwareSerial.h>
SoftwareSerial wfs(11, 10); // RX, TX
//SoftwareSerial wfs(8, 9); // RX, TX
static const long GasBaud = 9600;
//=========================================================================
void wifi_Init() {
  wfs.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  netStart();
  //netJoinAP(F("MMMM"),F("1234567890123"));
  //netJoinAP("acDev","AbroadCar2015()");
  //NetLinkTestBaidu();
}
void wfs_loop() {
  while (wfs.available()) {
    char c = wfs.read();
    lgs.write(c);
  }
}
//=========================================================================
char prSend[12] = "AT+CIPSEND=";
//=========================================================================
void netStart() {
  wfs.println(F("AT"));           smartDelay(1000);
  wfs.println(F("AT+CWJAP?"));    smartDelay(1000);//SeeAP
  wfs.println(F("AT+CIFSR"));     smartDelay(1000);//seesIP
  wfs.println(F("AT+CWMODE=1"));  smartDelay(1000);//beWiFi
}
void netJoinAP(String s, String p) {
  wfs.println(F("AT"));           smartDelay(1000);
  wfs.println(F("AT+CWMODE=1"));  smartDelay(1000);//beWiFi
  wfs.println(F("AT+RST"));       smartDelay(3000);//reBoot
  wfs.println("AT+CWJAP=\"" + s + "\",\"" + p + "\""); smartDelay(10000);
  wfs.println(F("AT+CWJAP?"));    smartDelay(1000);//SeeAP
  wfs.println(F("AT+CIFSR"));     smartDelay(1000);//seesIP
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
  HttpGetPost(F("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80"), F("GET / HTTP/1.0\r\n\r\n") , 5); smartDelay(1000);
}
//-------------------------------------------------------------------------
