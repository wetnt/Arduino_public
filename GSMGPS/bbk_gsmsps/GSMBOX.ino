//---------------------------------------------------------------
//String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//String myurl ="www.boboking.com/!wap/index.htm";
//---------------------------------------------------------------
char CSQ[] = "AT+CSQ";
char CGA[] = "AT+CGATT?";
char SAP[] = "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";//setting the SAPBR, the connection type is using gprs
char APN[] = "AT+SAPBR=3,1,\"APN\",\"CMNET\"";//setting the APN, the second need you fill in your local apn server
char PBR[] = "AT+SAPBR=1,1";//setting the SAPBR, for detail you can refer to the AT command mamual
char HTP[] = "AT+HTTPINIT"; //init the HTTP request
//String URL = "AT+HTTPPARA=\"URL\",\"www.boboking.com/!wap/index.htm\"";//setting the httppara
char URLA[] = "AT+HTTPPARA=\"URL\",\"";
char URLB[] = "\"";
char ACT[] = "AT+HTTPACTION=0";//submit the request
char REA[] = "AT+HTTPREAD"; //read the data from the website you access
//char REAT[] = "AT+HTTPREAD=0,1000";
//---------------------------------------------------------------

void SubmitHttpInt()
{
  //---------------------------------------------------------------
  gsm.println(CSQ);  smartDelay(100);   ShowSerialData();
  gsm.println(CGA);  smartDelay(100);   ShowSerialData();
  gsm.println(SAP);  smartDelay(1000);  ShowSerialData();
  gsm.println(APN);  smartDelay(3000);  ShowSerialData();
  //gsm.println(PBR);  smartDelay(2000);  ShowSerialData();
  //gsm.println(HTP);  smartDelay(1000);  ShowSerialData();
  //---------------------------------------------------------------
}
void SubmitHttpRequest(int delaysecond)
{
  //http://hi.baidu.com/robotkoko/item/f36367ebf921678ec10d7559
  //---------------------------------------------------------------
  sprintf(URL, "%.55s%f,%f,%f,%f,%f,%d,%ld000", UseH, 39.5f, 116.7f, 50.0f, 8.0f, 18.0f, 6, 6);
  lgs.println(URL);
  //---------------------------------------------------------------
  gsm.println(URL);  smartDelay(1000);   ShowSerialData();
  gsm.println(ACT);  smartDelay(delaysecond * 1000);  ShowSerialData();
  //---------------------------------------------------------------
  //the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!mySerial.available());
  ShowSerialData();
  //---------------------------------------------------------------
  gsm.println(REA);  smartDelay(1000);   ShowSerialData();
  gsm.println("");
  //---------------------------------------------------------------
}

void ShowSerialData()
{
  //---------------------------------------------------------------
  //---------------------------------------------------------------
}

