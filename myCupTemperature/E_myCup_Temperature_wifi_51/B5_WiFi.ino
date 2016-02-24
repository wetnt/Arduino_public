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
  wifiRun = wfs_cmd_back(C(AT_Test), C(AT_OKss), C(AT_Empt), 1000); //test
  wifiRun = wfs_cmd_back(C(AT_Cmux), C(AT_OKss), C(AT_Empt), 1000); //be 1 LINK MODE
  wifiRun = wfs_cmd_back(C(AT_IsJP), C(AT_OKss), C(AT_Empt), 1000); wifiJP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiRun = wfs_cmd_back(C(AT_lgIP), C(AT_OKss), C(AT_Empt), 1000); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiIP); lgln(wifiJP);
  //-------------------------------------------------------
}
void netJoinAP(String n, String p) {
  //-------------------------------------------------------------------------
  String AT_Join = G(AT_JAPa) + n + G(AT_JAPb) + p + G(AT_JAPc);
  //-------------------------------------------------------------------------
  wifiRun = wfs_cmd_back(C(AT_Test), C(AT_OKss), C(AT_Empt), 1000 ); //test
  wifiRun = wfs_cmd_back(C(AT_Type), C(AT_OKss), C(AT_Empt), 1000 ); //beWiFi
  wifiRun = wfs_cmd_back(C(AT_Rest), C(AT_RstB), C(AT_Empt), 5000 ); //reBoot
  wifiRun = wfs_cmd_back(C(AT_Cmux), C(AT_OKss), C(AT_Empt), 1000 ); //lgln(s);//?
  //wifiRun = wfs_cmd_back(  AT_Join , C(AT_OKss), C(AT_Empt), 10000); //lgln(s);//joinAP
  wifiRun = wfs_cmd_back(C(AT_IsJP), C(AT_OKss), C(AT_Fail), 1000 ); wifiJP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiRun = wfs_cmd_back(C(AT_lgIP), C(AT_OKss), C(AT_Empt), 1000 ); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiIP); lgln(wifiJP); for (;;);
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
String senx = "";
void HttpGetPost(char link[], char text[], int seconds) {
  senx = G(AT_Send) + String( sizeof(text) + String(sizeof(text)).length() ); //lgln(senx);
  char* xxxx = StringTocharx(senx);
  wifiRun = wfs_cmd_back(link, C(AT_Cnet), C(AT_Errs), 2000 ); //lg(wifiBack); lg('='); lg(wifiRun); lg();
  wifiRun = wfs_cmd_back(xxxx, C(AT_Stat), C(AT_Errs), 2000 ); //lg(wifiBack); lg('='); lg(wifiRun); lg();//if (!wifiRun) return;
  wifiRun = wfs_cmd_back(text, C(AT_Clsd), C(AT_Empt), 20000); //lg(wifiBack); lg('='); lg(wifiRun); lg(); //if (!wifiRun) return;
}
//=========================================================================
void NetLinkTest_Baidu() {
  HttpGetPost("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80", "GET / HTTP/1.0\r\n\r\n" , 5); lgln(wifiBack);
}
void NetLinkTest_BBKGPS() {
  HttpGetPost("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80", "GET http://www.bbkgps.com/t.php HTTP/1.0\r\n\r\n" , 10); lgln(wifiBack);
}
//=========================================================================
//=========================================================================
//typedef struct charCheckSave {
//  int len = 0;
//  int inx = 0;
//  String str = "";
//  void init(String s) {
//    str = s; inx = 0;
//    len = s.length();
//    //lg("check=");lg(len); lg();
//  }
//  boolean check(char c) {
//    //lg("="); lg(c); lg("="); lg(inx); lg();
//    if (len == 0) return false;
//    if (inx == len - 1) {
//      inx = 0; return true;
//    }
//    if (str[inx] == c) inx++; else inx = 0;
//    return false;
//  }
//} charCheckSave;
typedef struct charCheckSave {
  int len = 0;
  int inx = 0;
  String str = "";
  void init(char s[]) {
    str = s; inx = 0;
    len = sizeof(s);
    //lg("check=");lg(len); lg();
  }
  boolean check(char c) {
    //lg("="); lg(c); lg("="); lg(inx); lg();
    if (len == 0) return false;
    if (inx == len - 1) {
      inx = 0; return true;
    }
    if (str[inx] == c) inx++; else inx = 0;
    return false;
  }
} charCheckSave;
//=========================================================================
charCheckSave ck1, ck2, ck5, ck6;
//=========================================================================
void wfs_serial_clear() {
  while (wfs.available() > 0) {
    char c = wfs.read();
    if (logKey) lg(c);
  }
}
boolean wfs_cmd_send(String comStr) {
  wfs_serial_clear(); wfs.print(comStr); //lg(comStr);
  smartDelay(1);
  return true;
}
boolean wfs_cmd_backAB(String comStr, char strOK[], char strNO[], long timeout) { //
  //-------------------------------------------------------
  boolean save = false; char c; unsigned long start = millis(); wifiBack = "";
  ck1.init(strOK);
  ck2.init(strNO);
  ck5.init(C(AT_Errs));
  ck6.init(C(AT_Busy));
  //------------------------------------------------------
  wfs_serial_clear(); wfs.println(comStr);
  //-------------------------------------------------------
  while (millis() - start < timeout) {
    //-------------------------------------------------------
    while (wfs.available() > 0) {
      //-----------------------------------
      c = wfs.read();
      if (c == '\0') continue;
      if (logKey) lg(c);
      //-----------------------------------
      if (ck1.check(c)) save = true;
      if (save) wifiBack += c;
      if (ck2.check(c)) save = false;
      //-----------------------------------
      //      if (ck1.check(c)) return true;
      //      if (ck2.check(c)) return false;
      if (ck5.check(c)) return false;
      //if (ck6.check(c)) smartDelay(1);
      //-----------------------------------
      //smartDelay(1);
      //-----------------------------------
    }
    //-------------------------------------------------------
    smartDelay(1);
    //-------------------------------------------------------
  }
  //-------------------------------------------------------
  return false;
  //-------------------------------------------------------
}
boolean wfs_cmd_back(char comStr[], char strOK[], char strNO[], long timeout) { //
  //-------------------------------------------------------
  char c; unsigned long start = millis();
  ck1.init(strOK);
  ck2.init(strNO);
  ck5.init(C(AT_Errs));
  ck6.init(C(AT_Busy));
  //------------------------------------------------------
  wfs_serial_clear(); wfs.println(comStr);
  //-------------------------------------------------------
  while (millis() - start < timeout) {
    //-------------------------------------------------------
    while (wfs.available() > 0) {
      //-----------------------------------
      c = wfs.read();
      if (c == '\0') continue;
      if (logKey) lg(c);
      //-----------------------------------
      wifiBack += c;
      //-----------------------------------
      if (ck1.check(c)) return true;
      if (ck2.check(c)) return false;
      if (ck5.check(c)) return false;
      if (ck6.check(c)) return false;//smartDelay(1);
      //-----------------------------------
      //smartDelay(1);
      //-----------------------------------
    } //smartDelay(1);
    //-------------------------------------------------------
  }
  //-------------------------------------------------------
  return false;
  //-------------------------------------------------------
}
//=========================================================================
