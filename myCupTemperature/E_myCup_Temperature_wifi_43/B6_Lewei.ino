//-------------------------------------------------------------------------
//static String Lewei_Keys = "4a7c908d0de946de96e041dd84834154";
//PROGMEM static const char Lewei_Link[] = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
//PROGMEM static const char Lewei_Head[] = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
//PROGMEM static const char Lewei_Usek[] = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
//PROGMEM static const char Lewei_Host[] = "Host: www.lewei50.com\r\n";
//PROGMEM static const char Lewei_LenA[] = "Content-Length: ";
//PROGMEM static const char Lewei_LenB[] = "\r\n";
//PROGMEM static const char Lewei_EndA[] = "Content-Type: application/x-www-form-urlencoded\r\n";
//PROGMEM static const char Lewei_EndB[] = "Connection: close\r\n\r\n";
//PROGMEM static const char Lewei_JsnA[] = "[{\"Name\":\"WDLD\",\"Value\":\"";
//PROGMEM static const char Lewei_JsnB[] = "\"}]";

//static const char Lewei_Link[] = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
////static const char Lewei_Head[] = "POST /api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
////static const char Lewei_Usek[] = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
////static const char Lewei_Host[] = "Host: www.lewei50.com\r\n";
//static const char Lewei_Head[] = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\nuserkey: 4a7c908d0de946de96e041dd84834154\r\nHost: www.lewei50.com\r\n";
//static const char Lewei_LenA[] = "Content-Length: ";
//static const char Lewei_LenB[] = "\r\n";
////static const char Lewei_Type[] = "Content-Type: text/html\r\n";
////static const char Lewei_Clos[] = "Connection: close\r\n\r\n";
static const char Lewei_JsnA[] = "[{\"Name\":\"WDLD\",\"Value\":\"";
static const char Lewei_JsnB[] = "\"}]";
//-------------------------------------------------------------------------
//static String Lewei_Post = "";
static String Lewei_Data = "";
//-------------------------------------------------------------------------
void Lewei_Loop() {
  lgln(F("Lewei_Loop..."));
  //NetLinkTest_Baidu();
  //NetLinkTest_BBKGPS();
  //return;

  Lewei_Data =  Lewei_JsnA + String(GetMyCupTemperature()) + Lewei_JsnB;
  int dn = Lewei_Data.length();

  //  Lewei_Post = String(Lewei_Head) +
  //               //String(Lewei_Usek) +
  //               //String(Lewei_Host) +
  //               String(Lewei_LenA) + String(dn) + String(Lewei_LenB) + "\r\n" +
  //               String(Lewei_Data) + "\r\n";// +
  //  //String(Lewei_Type) +String(Lewei_Clos);
  //  lgln("post="); lg(Lewei_Post); lg();
  //  HttpGetPost(Lewei_Link, Lewei_Post, 10);
  //  lg(wifiBack); lg('='); lg(); lg(wifiRun); lg();

  //-------------------------------------------------------------------------------
  wifiRun = wfs_cmd_back(F("AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80"), AT_Cnet, AT_Errs, 2000 );
  int tn = String(F("POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n"));
 String(F("userkey: 4a7c908d0de946de96e041dd84834154\r\n"));
 String(F("Host: www.lewei50.com\r\n")).length()
           + String(F("Content-Length: ")).length() + String(dn).length() + String(F("\r\n")).length()
           + String(F("\r\n")).length() + String(Lewei_Data).length() + String(F("\r\n")).length();           
  senx = String(AT_Send) + String( tn + String(tn).length() ); lgln(senx);
  wifiRun = wfs_cmd_back(senx, AT_Stat, AT_Errs, 2000 );

  wfs.print(F("POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n"));
  wfs.print(F("userkey: 4a7c908d0de946de96e041dd84834154\r\n"));
  wfs.print(F("Host: www.lewei50.com\r\n"));
  wfs.print(F("Content-Length: ")); wfs.print(dn); wfs.print(F("\r\n"));
  wfs.print(F("\r\n")); wfs.print(Lewei_Data); wfs.print(F("\r\n"));
  wifiRun = wfs_cmd_back(F("\r\n"), AT_Clsd, AT_Empt, 20000);

}
//-------------------------------------------------------------------------
