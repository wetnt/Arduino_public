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
static String wifiJP = "", wifiIP = "";
//-------------------------------------------------------------------------
static const char AT_OKss[] = "OK";
static const char AT_Errs[] = "ERROR";
static const char AT_RstB[] = "Ai-Thinker";
static const char AT_Fail[] = "FAIL";
static const char AT_Cnet[] = "CONNECT";
static const char AT_Clsd[] = "CLOSED";
static const char AT_Empt[] = "";
//=========================================================================
#include <SoftwareSerial.h>
SoftwareSerial wfs(10, 11); // RX, TX
static const long GasBaud = 9600;
boolean logKey = false;
String wifiBack = "";
String data = ""; 
boolean wifiRun = false;
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
  wifiBack = wfs_cmd_back(AT_Test, 1000, AT_OKss, AT_Empt, &wifiRun); //lg(AT_Test); lg('='); lg(wifiBack); lg('='); lg(wifiRun); lg();for (;;);//test
  wifiBack = wfs_cmd_back(AT_Cmux, 1000, AT_OKss, AT_Empt, &wifiRun); //be 1 LINK MODE
  wifiBack = wfs_cmd_back(AT_IsJP, 1000, AT_OKss, AT_Empt, &wifiRun); wifiJP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //SeeAP
  wifiBack = wfs_cmd_back(AT_lgIP, 1000, AT_OKss, AT_Empt, &wifiRun); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiIP); lgln(wifiJP); 
  //-------------------------------------------------------
}
void netJoinAP(String n, String p) {
  //-------------------------------------------------------------------------
  String AT_Join = AT_JAPa + n + AT_JAPb + p + AT_JAPc;
  //-------------------------------------------------------------------------
  wifiBack = wfs_cmd_back(AT_Test, 1000 , AT_OKss, AT_Empt, &wifiRun); //test
  wifiBack = wfs_cmd_back(AT_Type, 1000 , AT_OKss, AT_Empt, &wifiRun); //beWiFi
  wifiBack = wfs_cmd_back(AT_Rest, 5000 , AT_RstB, AT_Empt, &wifiRun); //reBoot
  wifiBack = wfs_cmd_back(AT_Cmux, 1000 , AT_OKss, AT_Empt, &wifiRun); //lgln(s);//?
  wifiBack = wfs_cmd_back(AT_Join, 10000, AT_OKss, AT_Empt, &wifiRun); //lgln(s);//joinAP
  wifiBack = wfs_cmd_back(AT_IsJP, 1000 , AT_OKss, AT_Fail, &wifiRun); wifiJP = GetStringAB(wifiBack, F("\""), F("\"\r\n"));//SeeAP
  wifiBack = wfs_cmd_back(AT_lgIP, 1000 , AT_OKss, AT_Empt, &wifiRun); wifiIP = GetStringAB(wifiBack, F("\""), F("\"\r\n")); //seesIP
  //lgln(wifiIP); lgln(wifiJP); for (;;);
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
void HttpGetPost(String link, String text, int seconds) {
  int n = text.length() + String(text.length()).length();
  String senx = String(AT_Send) + String(n); lgln(senx);
  wifiBack = wfs_cmd_back(link, 2000 , AT_Cnet, AT_Errs, &wifiRun); //lg(wifiBack); lg('='); lg(wifiRun); lg();
  wifiBack = wfs_cmd_back(senx, 2000 , AT_Stat, AT_Errs, &wifiRun); //lg(wifiBack); lg('='); lg(wifiRun); lg();//if (!wifiRun) return;
  wifiBack = wfs_cmd_back(text, 20000, AT_Clsd, AT_Empt, &wifiRun); //lg(wifiBack); lg('='); lg(wifiRun); lg(); //if (!wifiRun) return;
}
//=========================================================================
void NetLinkTestBaidu() {
  //HttpGetPost2(F("AT+CIPSTART=\"TCP\",\"www.baidu.com\",80"), F("GET / HTTP/1.0\r\n\r\n") , 5); smartDelay(1000);
  HttpGetPost(F("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80"), F("GET http://www.bbkgps.com/t.php HTTP/1.0\r\n\r\n") , 10);// smartDelay(1000);
  lgln(wifiBack);
}
//=========================================================================
void wfs_serial_clear() {
  while (wfs.available() > 0) {
    char c = wfs.read();
    if (logKey) lg(c);
  }
}
void wfs_cmd_back(String comStr, long timeout, String strOK, String strNO, bool *backOK) { //target
  //lg(comStr); lg();
  //-------------------------------------------------------
  data = ""; 
  char c; unsigned long start = millis();
  //------------------------------------------------------
  wfs_serial_clear(); wfs.println(comStr);
  //-------------------------------------------------------
  while (millis() - start < timeout) {
    //-------------------------------------------------------
    while (wfs.available() > 0) {
      c = wfs.read(); //if (c == '\0') continue;
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
  backOK = false; 
  //return data;
  //-------------------------------------------------------
}
//=========================================================================
