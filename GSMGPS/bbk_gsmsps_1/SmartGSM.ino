//-------------------------------------------------------------------------
String URL = "";
String URLA = "AT+HTTPPARA=\"URL\",\"";
String UseH = "www.bbkgps.com/v/g.php?n=boboking&p=123xjp&g=";
String URLM = "";
String URLD = "\"";
//-------------------------------------------------------------------------
//String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//String myurl ="www.boboking.com/!wap/index.htm";
//-------------------------------------------------------------------------
char ATS[] = "AT";
char GMR[] = "AT+GMR";//模块版本
char CBC[] = "AT+CBC";//模块电压
char PIN[] = "AT+CPIN";//SIM状态

char CSQ[] = "AT+CSQ";//信号强度
char CRE[] = "AT+CREG?";//GSM网络状态
char CEG[] = "AT+CGREG?";//GPRS网络状态

char ATD[] = "ATD13911969356;";//打电话
char ATH[] = "ATH";//挂电话
char ATA[] = "ATA";//接电话
char RIN[] = "RING";

char CGA[] = "AT+CGATT?";
char SAP[] = "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";
char APN[] = "AT+SAPBR=3,1,\"APN\",\"CMNET\"";
char PNT[] = "AT+HTTPINIT";
char SA1[] = "AT+SAPBR=1,1";
char SA2[] = "AT+SAPBR=2,1";
//-------------------------------------------------------------------------
char ACT[] = "AT+HTTPACTION=0";
char REA[] = "AT+HTTPREAD";
//-------------------------------------------------------------------------
SmartSerial gprs;
bool GsmIsRun = false;
//-------------------------------------------------------------------------
void GprsOpenTest() {
  //---------------------------------------------------------------
  lgln(F("GSM-Serial3.start.test"));
  //--------------------------------------------
  GsmIsRun = gprs.CmdSendOK(ATS, 2); lg(GsmIsRun); lgln("");
  while (!GsmIsRun) {
    gsmStart();
    GsmIsRun = gprs.CmdSendOK(ATS, 2); lg(GsmIsRun); lgln("");
    smartDelay(5 * 1000);
  }
  //--------------------------------------------
  lgln(F("GSM-Serial3.started.isRun!"));
  //---------------------------------------------------------------
  if (!GsmIsRun) return;
  //---------------------------------------------------------------
  int t = 200; bool r = false;
  //-----------------------------------------------------------------------------
  //smartDelay(t); r = gprs.CmdSendOK(GMR, 1);  lg(r); lgln(""); smartDelay(t); //模块版本
  //smartDelay(t); r = gprs.CmdSendOK(CBC, 1);  lg(r); lgln(""); smartDelay(t); //模块电压
  //smartDelay(t); r = gprs.CmdSendOK(PIN, 1);  lg(r); lgln(""); smartDelay(t); //SIM状态
  //-----------------------------------------------------------------------------
  smartDelay(t); r = gprs.CmdSendOK(CSQ, 2);  lg(r); lgln(""); smartDelay(t);
  smartDelay(t); r = gprs.CmdSendOK(CRE, 2);  lg(r); lgln(""); smartDelay(t);
  smartDelay(t); r = gprs.CmdSendOK(CGA, 2);  lg(r); lgln(""); smartDelay(t);
  smartDelay(t); r = gprs.CmdSendOK(SAP, 2);  lg(r); lgln(""); smartDelay(t);
  smartDelay(t); r = gprs.CmdSendOK(APN, 2);  lg(r); lgln(""); smartDelay(t);
  //-----------------------------------------------------------------------------
  smartDelay(t); r = gprs.CmdSendOK(PNT, 2);  lg(r); lgln(""); smartDelay(t);
  smartDelay(t); r = gprs.CmdSendOK(SA1, 2);  lg(r); lgln(""); smartDelay(t);
  smartDelay(t); r = gprs.CmdSendOK(SA2, 2);  lg(r); lgln(""); smartDelay(t);
  //-----------------------------------------------------------------------------
}

void GprsHttpSend() {
  //-----------------------------------------------------------------------
  if ( !GsmIsRun ) return; lgln( "GprsHttpSend..." );
  //-----------------------------------------------------------------------
  URLM =
    String(gs.w) + String(",") + String(gs.j) + String(",") +
    String(g.h) + String(",") + String(g.v) + String(",") +
    String(g.x)  + String(",") + String(g.r) + String(",") + String(g.tu);
  URL = URLA + UseH + URLM + URLD;
  //-----------------------------------------------------------------------
  //String URL = "AT+HTTPPARA=\"URL\",\"http://www.bbkgps.com/index.htm\"";
  //String URL = "AT+HTTPPARA=\"URL\",\"http://www.bbkgps.com/t.php\"";
  //-----------------------------------------------------------------------
  int t = 500;  String k = ""; bool r = false;
  smartDelay(t); r = gprs.CmdSendOK(URL, 5); lgln(k); smartDelay(t);
  smartDelay(t); r = gprs.CmdSendOK(ACT, 5); lgln(k); smartDelay(5 * 1000);
  smartDelay(t); k = gprs.CmdSend(REA, "OK", "", 5); lgln(k); smartDelay(t);
  //---------------------------------------------------------------
}
//=========================================================================
long gprsRunTime = 0;
long gprsLstTime = 0;
long gprsRunTimeKey = 30 * 1000;//发送时长
//=========================================================================
String RingData = "";
void RingCheck(char a) {
  //---------------------------------------
  RingData = RingData + a;
  if (a == '\n') {
    lg( RingData );
    RingData = "";
    return;
  }
  //---------------------------------------
  if ( !DataIndexOf(RingData, RIN) ) return;
  RingData = "";
  //---------------------------------------
  smartDelay(2000);
  lgln(gprs.CmdSend(ATH, "OK", "", 10));
  //---------------------------------------
  gprsRunTime = millis();
  lgln( "RingCheck == gprsRunTime = millis()" );
  //---------------------------------------
}
void GprsRun() {
  //-----------------------------------------------------
  if (millis() - gprsLstTime < 10 * 1000  ) return;
  if (millis() - gprsRunTime > gprsRunTimeKey  ) return;
  //-----------------------------------------------------
  gprsLstTime = millis();
  GprsHttpSend();
  //-----------------------------------------------------
}
//=========================================================================
