//String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//String myurl ="www.boboking.com/!wap/index.htm";
//String myurl ="www.google.com.hk";

String CSQ = "AT+CSQ";
String CGA = "AT+CGATT?";
String SAP = "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";//setting the SAPBR, the connection type is using gprs
String APN = "AT+SAPBR=3,1,\"APN\",\"CMNET\"";//setting the APN, the second need you fill in your local apn server
String PBR = "AT+SAPBR=1,1";//setting the SAPBR, for detail you can refer to the AT command mamual
String HTP = "AT+HTTPINIT"; //init the HTTP request
String URL = "AT+HTTPPARA=\"URL\",\""+myurl+"\"";//setting the httppara
String ACT = "AT+HTTPACTION=0";//submit the request 
String REA = "AT+HTTPREAD"; //read the data from the website you access
String REAT = "AT+HTTPREAD=0,1000";


void SubmitHttpRequest(String myurl,int delaysecond)
{
  //---------------------------------------------------------------
  URL = "AT+HTTPPARA=\"URL\",\""+myurl+"\"";//setting the httppara
  //---------------------------------------------------------------  
  mySerial.println(CSQ);  delay(100);    ShowSerialData();  
  mySerial.println(CGA);  delay(100);    ShowSerialData(); 
  mySerial.println(SAP);  delay(1000);   ShowSerialData(); 
  mySerial.println(APN);  delay(3000);   ShowSerialData();
  //mySerial.println(PBR);  delay(2000);  ShowSerialData();
  //mySerial.println(HTP);  delay(2000);  ShowSerialData();
  mySerial.println(URL);  delay(1000);   ShowSerialData();
  mySerial.println(ACT);  delay(delaysecond*1000);  ShowSerialData();
  //---------------------------------------------------------------
  //the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!mySerial.available()); 
  ShowSerialData();
  //---------------------------------------------------------------
  mySerial.println(REA);  delay(2000);   ShowSerialData(); 
  //---------------------------------------------------------------
  mySerial.println("");   delay(1000);
  //---------------------------------------------------------------
}

void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}

// if(Serial.available())
// {
//    unsigned char input = Serial.read();
//    mySerial.write(input); 
// }
// if( mySerial.available())
//{ 
//    unsigned char input2 = mySerial.read();
//    Serial.write(input2);
//}

