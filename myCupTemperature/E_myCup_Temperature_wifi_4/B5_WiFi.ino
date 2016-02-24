//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
#include <SoftwareSerial.h>
SoftwareSerial wfs(10, 11); // RX, TX
static const long GasBaud = 9600;
boolean logKey = false;
//String wifiJP = "";
//String wifiIP = "";
String wifiBack = "";
boolean wifiRun = false;
//=========================================================================
void wifi_Init(boolean lgKey, boolean startAP, boolean joinAP, boolean test) {
  //-------------------------------------------------------------------------
  wfs.begin(GasBaud); lg(F("WiFi.Serial.start! = ")); lg(GasBaud); lg();
  //-------------------------------------------------------------------------
  logKey = lgKey;
  //-------------------------------------------------------------------------
  if (startAP) netStartAP();
  if (joinAP) netJoinAP(F("MMMM"), F("1234567890123"));//netJoinAP(F("acDev"), F("AbroadCar2015()"));
  //-------------------------------------------------------------------------
  //lgln(wifiIP); lgln(wifiJP);
  //-------------------------------------------------------------------------
  if (test) NetLinkTestBaidu();
  //-------------------------------------------------------------------------
}
//=========================================================================
void wfs_serial_clear() {
  while (wfs.available() > 0) wfs.read();
}
String wfs_cmd_back(String comStr, long timeout, String strOK, String strNO, bool *backOK, boolean logKey) { //target
  //-------------------------------------------------------
  String data = ""; char c; unsigned long start = millis();
  //------------------------------------------------------
  wfs_serial_clear(); wfs.println(comStr);
  //-------------------------------------------------------
  while (millis() - start < timeout) {
    //-------------------------------------------------------
    while (wfs.available() > 0) {
      c = wfs.read(); if (c == '\0') continue;
      data += c;
      if (logKey) lg(c);
    }
    smartDelay(1);
    //-------------------------------------------------------
    if ( strOK.length() > 0 && data.indexOf(strOK) != -1 )     {
      *backOK = true; break;
    }
    if ( strNO.length() > 0 && data.indexOf(strNO) != -1 )     {
      *backOK = false; break;
    }
    if (                       data.indexOf(F("ERROR")) != -1 )  {
      *backOK = false; break;
    }
    if (                       data.indexOf(F("CLOSED")) != -1 )  {
      *backOK = false; break;
    }
    if (                       data.indexOf(F("busy")) != -1 )  {
      *backOK = false; break;
    }
    //-------------------------------------------------------
  }
  //-------------------------------------------------------
  backOK = false; return data;
  //-------------------------------------------------------
}
void netStartAP() {
  //-------------------------------------------------------
  wifiBack = wfs_cmd_back(  F("AT"),          1000, F("OK"), ""         , &wifiRun, false);
  wifiBack = wfs_cmd_back(  F("AT+CWMODE=1"), 1000, F("OK"), ""         , &wifiRun, false);
  wifiBack = wfs_cmd_back(  F("AT+CWJAP?"),   1000, F("OK"), F("FAIL")  , &wifiRun, false); //wifiJP = GetStringAB(wifiBack, "\"", "\"\r\n");
  wifiBack = wfs_cmd_back(  F("AT+CIFSR"),    1000, F("OK"), ""         , &wifiRun, false); //wifiIP = GetStringAB(wifiBack, "\"", "\"\r\n");
  //lgln(wifiIP); lgln(wifiJP); for (;;);
  //-------------------------------------------------------
}
void netJoinAP(String n, String p) {
  //-------------------------------------------------------------------------
  wifiBack = wfs_cmd_back(  F("AT")                                 , 1000 , F("OK"), ""         , &wifiRun, false);
  wifiBack = wfs_cmd_back(  F("AT+CWMODE=1")                        , 1000 , F("OK"), ""         , &wifiRun, false); //beWiFi
  wifiBack = wfs_cmd_back(  F("AT+RST")                             , 1000 , F("Ai-Thinker"), "" , &wifiRun, false); //reBoot
  wifiBack = wfs_cmd_back(  F("AT+CIPMUX=0")                        , 1000 , F("OK"), ""         , &wifiRun, false); //lgln(s);//?
  wifiBack = wfs_cmd_back(  "AT+CWJAP=\"" + n + "\",\"" + p + "\""  , 10000, F("OK"), ""         , &wifiRun, false); //lgln(s);//joinAP
  wifiBack = wfs_cmd_back(  F("AT+CWJAP?")                          , 1000 , F("OK"), F("FAIL")  , &wifiRun, false); //wifiJP = GetStringAB(wifiBack, "\"", "\"\r\n"); //SeeAP
  wifiBack = wfs_cmd_back(  F("AT+CIFSR")                           , 1000 , F("OK"), ""         , &wifiRun, false); //wifiIP = GetStringAB(wifiBack, "\"", "\"\r\n"); //seesIP
  //lgln(wifiIP); lgln(wifiJP); for (;;);
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
//void HttpGetPost(String link, String text, int seconds) {
//  int n = text.length() + 2;
//  wfs.println(link); smartDelay(2000);
//  wfs.print(F("AT+CIPSEND=")); wfs.println(n); smartDelay(1000); //wfs.println(prSend + String(n));smartDelay(1000);
//  wfs.println(text); HttpBufferClear(); smartDelay(seconds * 1000);
//}
void HttpGetPost2(String link, String text, int seconds) {

  wifiBack = wfs_cmd_back( link, 2000 , F("CONNECT"), F("ERROR"), &wifiRun, true); lg(wifiBack); lg('='); lg(wifiRun); lg();
  if (!wifiRun) return;

  //int n = text.length() + String(text.length()).length();
  String s = "AT+CIPSEND=" + getDataN(); lgln(s);
  wifiBack = wfs_cmd_back( s, 2000 , F(">"), F("ERROR"), &wifiRun, true); lg(wifiBack); lg('='); lg(wifiRun); lg();
  if (!wifiRun) return;

  lgln(text);
  wifiBack = wfs_cmd_back( text, 5000 , F(">"), F("ERROR"), &wifiRun, true);
  lg(wifiBack); lg('='); lg(wifiRun); lg();
  if (!wifiRun) return;

  //  wfs.print(F("AT+CIPSEND=")); wfs.println(n); smartDelay(1000); //wfs.println(prSend + String(n));smartDelay(1000);
  //  wfs.println(text); HttpBufferClear(); smartDelay(seconds * 1000);


}
//=========================================================================
void NetLinkTestBaidu() {
  HttpGetPost2(F("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80"), F("GET / HTTP/1.0\r\n\r\n") , 5); smartDelay(1000);
}
//=========================================================================
