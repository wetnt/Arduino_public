//---------------------------------------------------------------  
unsigned long GsmShowTime = millis(), GsmShowTimeKey = 10*1000;//30s
//---------------------------------------------------------------  
void GSMloop() 
{
  //---------------------------------------------------------------  
  if( millis() - GsmShowTime < GsmShowTimeKey) return; 
  GsmShowTime = millis();
  //---------------------------------------------------------------  
  SubmitHttpRequest(10);
  //---------------------------------------------------------------  
}

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
  Serial.println(CSQ);  delay(100);
  Serial.println(CGA);  delay(100);
  Serial.println(SAP);  delay(1000);
  Serial.println(APN);  delay(3000);
  //---------------------------------------------------------------  
}
void SubmitHttpRequest(int delaysecond)
{
  //http://hi.baidu.com/robotkoko/item/f36367ebf921678ec10d7559
  //---------------------------------------------------------------
  //sprintf(URL,"%.55s%f,%f,%f,%f,%f,%d,%ld000",UseH,WW,JJ,HH,VV,FX,SR,mytime);
  sprintf(
    URL,
  "%.23s%.55s%.9s,%.10s,%s,%s,%s,%ld000%.3s",
    URLA,UseH,gs.sLats,gs.sLons,gs.sHigh,gs.sSped,gs.sFans,utctime,URLB
  );
  //---------------------------------------------------------------  
  //Serial.println(URLA);
  Serial.println(URL);  
  //Serial.println(URLB); 
  delay(100);
  Serial.println(ACT);  delay(delaysecond*1000);
  //---------------------------------------------------------------  
  Serial.println(REA);  delay(1000);  Serial.println();
  //---------------------------------------------------------------
}
