//-------------------------------------------------------------------------
char URL[130];
char UseH[] = "www.boboking.com/v/g.php?n=boboking&p=123xjp&g=";
//-------------------------------------------------------------------------
//String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//String myurl ="www.boboking.com/!wap/index.htm";
//---------------------------------------------------------------
//AT+CSQ
//AT+CREG?
//AT+CGATT?;
//---------------------------
//AT+SAPBR=3,1,"CONTYPR","GPRS"
//AT+SAPBR=3,1,"APN","CMNET"
//AT+SAPBR=1,1
//AT+SAPBR=2,1
//---------------------------
//AT+HTTPPARA="URL","www.bbkgps.com/index.htm"
//AT+HTTPACTION=0     //+HTTPACTION
//AT+HTTPREAD
//---------------------------------------------------------------
char CSQ[] = "AT+CSQ";
char CRE[] = "AT+CREG?";
char CGA[] = "AT+CGATT?;";
char SAP[] = "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";
char APN[] = "AT+SAPBR=3,1,\"APN\",\"CMNET\"";
char PNT[] = "AT+HTTPINIT";
char SA1[] = "AT+SAPBR=1,1";
char SA2[] = "AT+SAPBR=2,1";
//---------------------------------------------------------------
//char URL[] = "AT+HTTPPARA=\"URL\",\"www.bbkgps.com/index.htm\"";
char ACT[] = "AT+HTTPACTION=0";
char REA[] = "AT+HTTPREAD";
//---------------------------------------------------------------

void SubmitHttpInt() {
  //---------------------------------------------------------------
  gsm.println(CSQ); smartDelay(1000);
  gsm.println(CRE); smartDelay(1000);
  gsm.println(CGA); smartDelay(1000);
  //---------------------------------------
  gsm.println(SAP); smartDelay(1000);
  gsm.println(APN); smartDelay(5000);
  gsm.println(PNT); smartDelay(5000);
  //---------------------------------------
  gsm.println(SA1); smartDelay(3000);
  gsm.println(SA2); smartDelay(3000);
  //---------------------------------------------------------------
}
void SubmitHttpRequest(int delaysecond) {
  //http://hi.baidu.com/robotkoko/item/f36367ebf921678ec10d7559
  //---------------------------------------------------------------
  sprintf(URL, "%.55s%f,%f,%f,%f,%f,%d,%ld000", UseH, g.w, g.j, g.h, g.v, g.x, g.r, g.n);
  lgs.println(URL);
  //---------------------------------------------------------------
  gsm.println(URL); smartDelay(1000);
  gsm.println(ACT); smartDelay(delaysecond * 1000);
  gsm.println(REA); smartDelay(1000);
  gsm.println("");
  //---------------------------------------------------------------
}
