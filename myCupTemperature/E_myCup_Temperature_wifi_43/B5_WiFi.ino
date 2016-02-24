//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
static const char AT_Test[] = "AT";
static const char AT_Type[] = "AT+CWMODE=1"; //beWiFi
static const char AT_Rest[] = "AT+RST";       //reBoot
static const char AT_Cmux[] = "AT+CIPMUX=0";  //?
static const char AT_IsJP[] = "AT+CWJAP?";    //SeeAP//is Join AP
static const char AT_lgIP[] = "AT+CIFSR";     //seesIP
static const char AT_JAPa[] = "AT+CWJAP=\"";  //Join AP
static const char AT_JAPb[] = "\",\"";        //
static const char AT_JAPc[] =  "\"";          //
static const char AT_Send[] = "AT+CIPSEND=";  //
static const char AT_Stat[] = ">";            //
//-------------------------------------------------------------------------
static String wifiJP = "", wifiIP = "";
//-------------------------------------------------------------------------
static const char AT_OKss[] = "OK";
static const char AT_Errs[] = "ERROR";
static const char AT_RstB[] = "Ai-Thinker";
static const char AT_Fail[] = "FAIL";
static const char AT_Cnet[] = "CONNECT";
static const char AT_Clsd[] = "CLOSED";
static const char AT_Empt[] = "";
//static const char AT_SdOK[] = "SEND OK";
//static const char AT_SdFL[] = "SEND FAIL";
//=========================================================================

//=========================================================================
#include <SoftwareSerial.h>
SoftwareSerial wfs(10, 11); // RX, TX
static const long GasBaud = 9600;
boolean logKey = false;
boolean wifiRun = false;
String wifiBack = "";
//=========================================================================
void wifi_Init(boolean lgKey, boolean startAP, boolean joinAP) {
  //-------------------------------------------------------------------------
  wfs.begin(GasBaud); lg(F("WiFi.Serial.start! = ")); lg(GasBaud); lg();
  //-------------------------------------------------------------------------
  logKey = lgKey;
  //-------------------------------------------------------------------------
  if (startAP) netStartAP();
  if (joinAP) netJoinAP(F("MMMM"), F("1234567890123"));//netJoinAP(F("acDev"), F("AbroadCar2015()"));
  lgln(wifiIP); lgln(wifiJP);
  //-------------------------------------------------------------------------
}
//=========================================================================
void netStartAP() {
  //-------------------------------------------------------
  wifiRun = wfs_cmd_back(AT_Test, AT_OKss, AT_Empt, 1000); //lg(AT_Test); lg('='); lg(wifiBack); lg('='); lg(wifiRun); lg();for (;;);//test
  wifiRun = wfs_cmd_back(AT_Cmux, AT_OKss, AT_Empt, 1000); //be 1 LINK MODE
  wifiRun = wfs_cmd_back(AT_IsJP, AT_OKss, AT_Empt, 1000); wifiJP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiRun = wfs_cmd_back(AT_lgIP, AT_OKss, AT_Empt, 1000); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiIP); lgln(wifiJP);
  //-------------------------------------------------------
}
void netJoinAP(String n, String p) {
  //-------------------------------------------------------------------------
  String AT_Join = AT_JAPa + n + AT_JAPb + p + AT_JAPc;
  //-------------------------------------------------------------------------
  wifiRun = wfs_cmd_back(AT_Test, AT_OKss, AT_Empt, 1000 ); //test
  wifiRun = wfs_cmd_back(AT_Type, AT_OKss, AT_Empt, 1000 ); //beWiFi
  wifiRun = wfs_cmd_back(AT_Rest, AT_RstB, AT_Empt, 5000 ); //reBoot
  wifiRun = wfs_cmd_back(AT_Cmux, AT_OKss, AT_Empt, 1000 ); //lgln(s);//?
  wifiRun = wfs_cmd_back(AT_Join, AT_OKss, AT_Empt, 10000); //lgln(s);//joinAP
  wifiRun = wfs_cmd_back(AT_IsJP, AT_OKss, AT_Fail, 1000 ); wifiJP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiRun = wfs_cmd_back(AT_lgIP, AT_OKss, AT_Empt, 1000 ); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiIP); lgln(wifiJP); for (;;);
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
String senx = "";
void HttpGetPost(String link, String text, int seconds) {
  senx = String(AT_Send) + String( text.length() + String(text.length()).length() ); lgln(senx);
  wifiRun = wfs_cmd_back(link, AT_Cnet, AT_Errs, 2000 ); //lg(wifiBack); lg('='); lg(wifiRun); lg();
  wifiRun = wfs_cmd_back(senx, AT_Stat, AT_Errs, 2000 ); //lg(wifiBack); lg('='); lg(wifiRun); lg();//if (!wifiRun) return;
  wifiRun = wfs_cmd_back(text, AT_Clsd, AT_Empt, 20000); //lg(wifiBack); lg('='); lg(wifiRun); lg(); //if (!wifiRun) return;
}
//=========================================================================
void NetLinkTest_Baidu() {
  HttpGetPost(F("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80"), F("GET / HTTP/1.0\r\n\r\n") , 5); lgln(wifiBack);
}
void NetLinkTest_BBKGPS() {
  HttpGetPost(F("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80"), F("GET http://www.bbkgps.com/t.php HTTP/1.0\r\n\r\n") , 10); lgln(wifiBack);
}
//=========================================================================
void wfs_serial_clear() {
  while (wfs.available() > 0) {
    char c = wfs.read();
    if (logKey) lg(c);
  }
}
boolean wfs_cmd_back(String comStr, String strOK, String strNO, long timeout) { //target
  //lg(comStr); lg();
  //-------------------------------------------------------
  char c; unsigned long start = millis(); wifiBack = "";
  //------------------------------------------------------
  wfs_serial_clear(); wfs.println(comStr);
  //-------------------------------------------------------
  while (millis() - start < timeout) {
    //-------------------------------------------------------
    while (wfs.available() > 0) {
      c = wfs.read(); if (c == '\0') continue;
      wifiBack += c; if (logKey) lg(c);
    } smartDelay(1);
    //-------------------------------------------------------
    if ( strOK.length() > 0 && wifiBack.indexOf(strOK) != -1 ) return true;
    if ( strNO.length() > 0 && wifiBack.indexOf(strNO) != -1 ) return false;
    if (                  wifiBack.indexOf(F("ERROR")) != -1 ) return false;
    //if (               wifiBack.indexOf(F("CLOSED")) != -1 ) return false;
    if (                   wifiBack.indexOf(F("busy")) != -1 ) {
      smartDelay(2);
      //return false;
    }
    //-------------------------------------------------------
  }
  //-------------------------------------------------------
  return false;
  //-------------------------------------------------------
}
//=========================================================================
