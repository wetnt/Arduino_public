//---------------------------------------------------------------  
unsigned long GsmShowTime = millis(), GsmShowTimeKey = 15000;//30s
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
//---------------------------------------------------------------
void SubmitHttpInt()
{
  //---------------------------------------------------------------  
  Serial.println("AT+CSQ");  delay(100);
  Serial.println("AT+CGATT?");  delay(100);
  Serial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");  delay(1000);
  Serial.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");  delay(3000);
  //---------------------------------------------------------------  
}
void SubmitHttpRequest(int ds)
{
  //---------------------------------------------------------------
  sprintf(
    URL,
    "%.55s%.9s,%.10s,%s,%s,%s,%ld000",
    UseH,gs.sLats,gs.sLons,gs.sHigh,gs.sSped,gs.sFans,utctime
  );
  //---------------------------------------------------------------  
  Serial.print("AT+HTTPPARA=\"URL\",\"");
  Serial.print(URL); 
  Serial.println("\"");   delay(1000);
  Serial.println("AT+HTTPACTION=0");  delay(ds*1000); 
  Serial.println("AT+HTTPREAD");  delay(1000);
  //---------------------------------------------------------------
}

void feedgsm()
{
  //-------------------------------------------------------------------------
  while (Serial.available())
  {
    
  }
  //-------------------------------------------------------------------------
}
