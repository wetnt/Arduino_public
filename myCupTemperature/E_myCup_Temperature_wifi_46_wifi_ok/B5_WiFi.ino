//=========================================================================
//https://www.zybuluo.com/kfihihc/note/31135
//http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
//=========================================================================
const static char AT_Test[] PROGMEM = "AT";
const static char AT_Type[] PROGMEM = "AT+CWMODE=1"; //beWiFi
const static char AT_Rest[] PROGMEM = "AT+RST";       //reBoot
const static char AT_Cmux[] PROGMEM = "AT+CIPMUX=0";  //?
const static char AT_IsJP[] PROGMEM = "AT+CWJAP?";    //SeeAP//is Join AP
const static char AT_lgIP[] PROGMEM = "AT+CIFSR";     //seesIP
const static char AT_JAPa[] PROGMEM = "AT+CWJAP=\"";  //Join AP
const static char AT_JAPb[] PROGMEM = "\",\"";        //
const static char AT_JAPc[] PROGMEM =  "\"";          //
const static char AT_Send[] PROGMEM = "AT+CIPSEND=";  //
const static char AT_Stat[] PROGMEM = ">";            //
//-------------------------------------------------------------------------
const static char AT_OKss[] PROGMEM = "OK";
const static char AT_Busy[] PROGMEM = "busy";
const static char AT_Errs[] PROGMEM = "ERROR";
const static char AT_RstB[] PROGMEM = "Ai-Thinker";
const static char AT_Fail[] PROGMEM = "FAIL";
const static char AT_Cnet[] PROGMEM = "CONNECT";
const static char AT_Clsd[] PROGMEM = "CLOSED";
const static char AT_Empt[] PROGMEM = "";
//=========================================================================
static String wifiJP = "", wifiIP = "";
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
  wifiRun = wfs_cmd_back(G(AT_Test), G(AT_OKss), G(AT_Empt), 1000); //test
  wifiRun = wfs_cmd_back(G(AT_Cmux), G(AT_OKss), G(AT_Empt), 1000); //be 1 LINK MODE
  wifiRun = wfs_cmd_back(G(AT_IsJP), G(AT_OKss), G(AT_Empt), 1000); wifiJP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiRun = wfs_cmd_back(G(AT_lgIP), G(AT_OKss), G(AT_Empt), 1000); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiIP); lgln(wifiJP);
  //-------------------------------------------------------
}
void netJoinAP(String n, String p) {
  //-------------------------------------------------------------------------
  String AT_Join = G(AT_JAPa) + n + G(AT_JAPb) + p + G(AT_JAPc);
  //-------------------------------------------------------------------------
  wifiRun = wfs_cmd_back(G(AT_Test), G(AT_OKss), G(AT_Empt), 1000 ); //test
  wifiRun = wfs_cmd_back(G(AT_Type), G(AT_OKss), G(AT_Empt), 1000 ); //beWiFi
  wifiRun = wfs_cmd_back(G(AT_Rest), G(AT_RstB), G(AT_Empt), 5000 ); //reBoot
  wifiRun = wfs_cmd_back(G(AT_Cmux), G(AT_OKss), G(AT_Empt), 1000 ); //lgln(s);//?
  wifiRun = wfs_cmd_back(  AT_Join , G(AT_OKss), G(AT_Empt), 10000); //lgln(s);//joinAP
  wifiRun = wfs_cmd_back(G(AT_IsJP), G(AT_OKss), G(AT_Fail), 1000 ); wifiJP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiRun = wfs_cmd_back(G(AT_lgIP), G(AT_OKss), G(AT_Empt), 1000 ); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiIP); lgln(wifiJP); for (;;);
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
String senx = "";
void HttpGetPost(String link, String text, int seconds) {
  senx = G(AT_Send) + String( text.length() + String(text.length()).length() ); //lgln(senx);
  wifiRun = wfs_cmd_back(link, G(AT_Cnet), G(AT_Errs), 2000 ); //lg(wifiBack); lg('='); lg(wifiRun); lg();
  wifiRun = wfs_cmd_back(senx, G(AT_Stat), G(AT_Errs), 2000 ); //lg(wifiBack); lg('='); lg(wifiRun); lg();//if (!wifiRun) return;
  wifiRun = wfs_cmd_back(text, G(AT_Clsd), G(AT_Empt), 20000); //lg(wifiBack); lg('='); lg(wifiRun); lg(); //if (!wifiRun) return;
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
boolean wfs_cmd_send(String comStr) {
  wfs_serial_clear(); wfs.print(comStr); //lg(comStr);
  return true;
}
boolean wfs_cmd_back(String comStr, String strOK, String strNO, long timeout) { //
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
    if (                  wifiBack.indexOf(G(AT_Errs)) != -1 ) return false;
    if (                  wifiBack.indexOf(G(AT_Busy)) != -1 ) smartDelay(2);
    //-------------------------------------------------------
  }
  //-------------------------------------------------------
  return false;
  //-------------------------------------------------------
}
//=========================================================================
