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
String wifiAP = "", wifiIP = "";
//=========================================================================
#include <SoftwareSerial.h>
SoftwareSerial wfs(10, 11); // RX, TX
static const long GasBaud = 9600;
String wifiBack = "";
boolean logKey = false;
boolean wifiRun = false;
//=========================================================================
void wifi_Init(boolean lgKey, boolean startAP, boolean joinAP) {
  //-------------------------------------------------------------------------
  wfs.begin(GasBaud); lg(F("WiFi.Serial.start! = ")); lg(GasBaud); lg();
  //-------------------------------------------------------------------------
  logKey = lgKey;
  //-------------------------------------------------------------------------
  if (startAP) netStartAP();
  if (joinAP) netJoinAP(F("MMMM"), F("1234567890123"));
  if (joinAP) netJoinAP(F("JTWX"), F("jtwx1234"));
  //-------------------------------------------------------------------------
  lgln(wifiAP); lgln(wifiIP);
  //-------------------------------------------------------------------------
}
//=========================================================================
void netStartAP() {
  //-------------------------------------------------------
  wifiRun = wfs_cmd_back(S(AT_Test), S(AT_OKss), S(AT_Empt), 1000); //test
  wifiRun = wfs_cmd_back(S(AT_Cmux), S(AT_OKss), S(AT_Empt), 1000); //be 1 LINK MODE
  wifiRun = wfs_cmd_back(S(AT_IsJP), S(AT_OKss), S(AT_Empt), 1000); lgln(wifiBack); wifiAP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiRun = wfs_cmd_back(S(AT_lgIP), S(AT_OKss), S(AT_Empt), 1000); lgln(wifiBack); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiAP); lgln(wifiIP);
  //-------------------------------------------------------
}
void netJoinAP(String n, String p) {
  //-------------------------------------------------------------------------
  String AT_Join = S(AT_JAPa) + n + S(AT_JAPb) + p + S(AT_JAPc);
  //-------------------------------------------------------------------------
  wifiRun = wfs_cmd_back(S(AT_Test), S(AT_OKss), S(AT_Empt), 1000 ); //test
  wifiRun = wfs_cmd_back(S(AT_Type), S(AT_OKss), S(AT_Empt), 1000 ); //beWiFi
  wifiRun = wfs_cmd_back(S(AT_Rest), S(AT_RstB), S(AT_Empt), 5000 ); //reBoot
  wifiRun = wfs_cmd_back(S(AT_Cmux), S(AT_OKss), S(AT_Empt), 1000 ); //lgln(s);//?
  wifiRun = wfs_cmd_back(  AT_Join , S(AT_OKss), S(AT_Empt), 15000); //lgln(s);//joinAP
  wifiRun = wfs_cmd_back(S(AT_IsJP), S(AT_OKss), S(AT_Fail), 1000 ); wifiAP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiRun = wfs_cmd_back(S(AT_lgIP), S(AT_OKss), S(AT_Empt), 1000 ); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiAP); lgln(wifiIP); //for (;;);
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
String senx = "";
void HttpGetPost(String link, String text, int seconds) {
  senx = S(AT_Send) + String(text.length() + String(text.length()).length() ); //lgln(senx);
  wifiRun = wfs_cmd_back(link, S(AT_Cnet), S(AT_Errs), 2000 ); //lg(wifiBack); lg('='); lg(wifiRun); lg();
  wifiRun = wfs_cmd_back(senx, S(AT_Stat), S(AT_Errs), 2000 ); //lg(wifiBack); lg('='); lg(wifiRun); lg();//if (!wifiRun) return;
  wifiRun = wfs_cmd_back(text, S(AT_Clsd), S(AT_Empt), 20000); //lg(wifiBack); lg('='); lg(wifiRun); lg(); //if (!wifiRun) return;
}
//=========================================================================
const static char Link_Baidu[] PROGMEM = {"AT+CIPSTART=\"TCP\",\"www.baidu.com\",80"};
const static char Urls_Baidu[] PROGMEM = {"GET / HTTP/1.0\r\n\r\n"};
void NetLinkTest_Baidu() {
  HttpGetPost(S(Link_Baidu), S(Urls_Baidu) , 5); lgln(wifiBack);
}
const static char Link_BkGps[] PROGMEM = {"AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80"};
const static char Urls_BkGps[] PROGMEM = {"GET http://www.bbkgps.com/t.php HTTP/1.0\r\n\r\n"};
void NetLinkTest_BBKGPS() {
  HttpGetPost(S(Link_BkGps), S(Urls_BkGps) , 10); lgln(wifiBack);
}
//=========================================================================
//=========================================================================
typedef struct charCheckSave {
  int len = 0, inx = 0;
  String str = "";
  void init(String s) {
    str = String(s); inx = 0;
    len = s.length();
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
charCheckSave ck1, ck2, ck3, ck4, ck5;
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
boolean wfs_cmd_backAB(String comStr, String strOK, String strNO, long timeout) { //
  //-------------------------------------------------------
  boolean save = false; char c; unsigned long start = millis(); wifiBack = "";
  ck1.init(strOK);
  ck2.init(strNO);
  ck3.init(S(AT_Errs));
  ck4.init(S(AT_Busy));
  ck5.init(S(AT_Clsd));
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
      if (save) wifiBack += c;
      if (ck1.check(c)) save = true;
      if (ck2.check(c)) save = false;
      //-----------------------------------
      //if (ck3.check(c)) return true;
      //if (ck4.check(c)) return false;
      if (ck5.check(c)) return false;
      //-----------------------------------
      Tube4_loop();
      //-----------------------------------
    }
    //-------------------------------------------------------
    Tube4_loop();
    //-------------------------------------------------------
  }
  //-------------------------------------------------------
  return false;
  //-------------------------------------------------------
}
boolean wfs_cmd_back(String comStr, String strOK, String strNO, long timeout) { //
  //-------------------------------------------------------
  char c; unsigned long start = millis(); wifiBack = "";
  ck1.init(strOK);
  ck2.init(strNO);
  ck3.init(S(AT_Errs));
  ck4.init(S(AT_Busy));
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
      if (ck3.check(c)) return false;
      if (ck4.check(c)) return false;
      //-----------------------------------
      Tube4_loop();
      //-----------------------------------
    }
    //-------------------------------------------------------
    Tube4_loop();
    //-------------------------------------------------------
  }
  //-------------------------------------------------------
  return false;
  //-------------------------------------------------------
}
//=========================================================================
