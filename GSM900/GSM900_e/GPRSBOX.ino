//String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//String myurl ="www.boboking.com/!wap/index.htm";
//String myurl ="www.google.com.hk";

//static String CSQ = "AT+CSQ";
//static String CGA = "AT+CGATT?";
//static String SAP = "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";//setting the SAPBR, the connection type is using gprs
//static String APN = "AT+SAPBR=3,1,\"APN\",\"CMNET\"";//setting the APN, the second need you fill in your local apn server
//static String PBR = "AT+SAPBR=1,1";//setting the SAPBR, for detail you can refer to the AT command mamual
//static String HTP = "AT+HTTPINIT"; //init the HTTP request
//static String URL = "AT+HTTPPARA=\"URL\",\"www.boboking.com/!wap/index.htm\"";//setting the httppara
//static String ACT = "AT+HTTPACTION=0";//submit the request 
//static String REA = "AT+HTTPREAD"; //read the data from the website you access
//static String REAT = "AT+HTTPREAD=0,1000";


void SubmitHttpRequest(String myurl,int delaysecond)
{
  //---------------------------------------------------------------
  //URL = "AT+HTTPPARA=\"URL\",\""+myurl+"\"";//setting the httppara
  //---------------------------------------------------------------  
  //mySerial.println(CSQ);  delay(100);    ShowSerialData();  
  //mySerial.println(CGA);  delay(100);    ShowSerialData(); 
  //mySerial.println(SAP);  delay(1000);   ShowSerialData(); 
  //mySerial.println(APN);  delay(3000);   ShowSerialData();
  //mySerial.println(PBR);  delay(2000);  ShowSerialData();
  //mySerial.println(HTP);  delay(2000);  ShowSerialData();
  //mySerial.println(URL);  delay(1000);   ShowSerialData();
  //mySerial.println(ACT);  delay(delaysecond*1000);  ShowSerialData();
  //---------------------------------------------------------------
  //the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!mySerial.available()); 
  //ShowSerialData();
  //---------------------------------------------------------------
  //mySerial.println(REA);  delay(2000);   ShowSerialData(); 
  //---------------------------------------------------------------
  //mySerial.println("");   delay(1000);
  //---------------------------------------------------------------
}

void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}


void SubmitHttpRequestx() 
{ 
  //mySerial.println("AT+CSQ");     delay(100);   ShowSerialData();
  //mySerial.println("AT+CGATT?");  delay(100);   ShowSerialData();    
  //mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");   delay(1000);  ShowSerialData(); 
  //mySerial.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");      delay(4000);  ShowSerialData();    
  //mySerial.println("AT+SAPBR=1,1");  delay(2000);  ShowSerialData();
  //mySerial.println("AT+HTTPINIT");   delay(2000);  ShowSerialData(); 
  //mySerial.println("AT+HTTPPARA=\"URL\",\"www.baidu.com\""); delay(1000); ShowSerialData();
  //mySerial.println("AT+HTTPACTION=0");  delay(10000);
  //while(!mySerial.available()); 
  //ShowSerialData();    
  //mySerial.println("AT+HTTPREAD");  delay(300); ShowSerialData();
  //mySerial.println("");  delay(100); 
} 
