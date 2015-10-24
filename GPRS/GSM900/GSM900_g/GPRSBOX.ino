//String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//String myurl ="www.boboking.com/!wap/index.htm";
//String myurl ="www.google.com.hk";

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

void SubmitHttpInt()
{
  //---------------------------------------------------------------  
  GsmSerial.println(CSQ);  delay(100);   ShowSerialData();  
  GsmSerial.println(CGA);  delay(100);   ShowSerialData(); 
  GsmSerial.println(SAP);  delay(1000);  ShowSerialData(); 
  GsmSerial.println(APN);  delay(3000);  ShowSerialData();
  GsmSerial.println(PBR);  delay(2000);  ShowSerialData();
  GsmSerial.println(HTP);  delay(1000);  ShowSerialData();
  //---------------------------------------------------------------  
}
void SubmitHttpRequest(char URLX[],int delaysecond)
{
  //http://hi.baidu.com/robotkoko/item/f36367ebf921678ec10d7559
  //---------------------------------------------------------------
  //URL = String("AT+HTTPPARA=\"URL\",\""+myurl+"\"");//setting the httppara
  //URL = String( String(URLA) +""+ String(URLX) );
  //sprintf(URL,"%s%s%s",URLA,URLX,URLB);
  //strcpy(URL,URLA);
  //strcat(URL,URLX);
  //strcat(URL,URLB);
  //mySerial.println(URL);  delay(1000);   ShowSerialData();
  //Serial.print(URLA); Serial.print(URLX); Serial.print(URLB); Serial.println();
  GsmSerial.print(URLA); GsmSerial.print(URLX); GsmSerial.print(URLB); GsmSerial.println();
   //mySerial.print(URLA);  
   //mySerial.print("http://www.boboking.com/v/g.php?n=boboking&p=123xjp");  
   //mySerial.print("&t=");  
   //mySerial.print(YY,DEC);  
   //mySerial.print(MD,DEC);  
   //mySerial.print(DD,DEC);  
   //mySerial.print(HT,DEC);  
   //mySerial.print(MT,DEC);  
   //mySerial.print(ST,DEC); 
   //mySerial.print("&g=");  //38,112,50,46,80,99,1245678900000";
   //mySerial.print(WW,DEC);   Serial.print(","); 
   //mySerial.print(JJ,DEC);   Serial.print(","); 
   //mySerial.print(HH,DEC);   Serial.print(","); 
   //mySerial.print(VV,DEC);   Serial.print(","); 
   //mySerial.print(FX,DEC);   Serial.print(",");    
   //mySerial.print(YD,DEC);  
   //mySerial.print(MD,DEC);  
   //mySerial.print(DD,DEC);  
   //mySerial.print(HT,DEC);  
   //mySerial.print(MT,DEC);  
   //mySerial.print(ST,DEC);    
   //mySerial.print(URLB);  
   //mySerial.println();
  delay(1000);   ShowSerialData();  
  //---------------------------------------------------------------  
  GsmSerial.println(ACT);  delay(delaysecond*1000);  ShowSerialData();
  //---------------------------------------------------------------
  //the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!mySerial.available()); 
  ShowSerialData();
  //---------------------------------------------------------------  
  GsmSerial.println(REA);  delay(1000);   ShowSerialData(); 
  GsmSerial.println("");
  //---------------------------------------------------------------
}

void ShowSerialData()
{
  while(GsmSerial.available()!=0)
    Serial.write(GsmSerial.read());
}
