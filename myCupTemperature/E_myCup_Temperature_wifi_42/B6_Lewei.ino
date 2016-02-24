#include <avr/pgmspace.h>
//-------------------------------------------------------------------------
const static char Lewei_Link[] PROGMEM  = {"AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80"};
static const unsigned char Lewei_Head[] PROGMEM = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
static const unsigned char Lewei_Usek[] PROGMEM = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
static const unsigned char Lewei_Host[] PROGMEM = "Host: www.lewei50.com\r\n";
static const unsigned char Lewei_LenA[] PROGMEM = "Content-Length: ";
static const unsigned char Lewei_LenB[] PROGMEM = "\r\n";
static const unsigned char Lewei_EndA[] PROGMEM = "Content-Type: application/x-www-form-urlencoded\r\n";
static const unsigned char Lewei_EndB[] PROGMEM = "Connection: close\r\n\r\n";
static const char Lewei_JsnA[] PROGMEM = "[{\"Name\":\"WDLD\",\"Value\":\"";
static const unsigned char Lewei_JsnB[] PROGMEM = "\"}]";


//static String Lewei_Keys = "4a7c908d0de946de96e041dd84834154";
//PROGMEM static String Lewei_Link = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
//PROGMEM static String Lewei_Head = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
//PROGMEM static String Lewei_Usek = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
//PROGMEM static String Lewei_Host = "Host: www.lewei50.com\r\n";
//PROGMEM static String Lewei_LenA = "Content-Length: ";
//PROGMEM static String Lewei_LenB = "\r\n";
//PROGMEM static String Lewei_EndA = "Content-Type: application/x-www-form-urlencoded\r\n";
//PROGMEM static String Lewei_EndB = "Connection: close\r\n\r\n";
//PROGMEM static String Lewei_JsnA = "[{\"Name\":\"WDLD\",\"Value\":\"";
//PROGMEM static String Lewei_JsnB = "\"}]";

//static const char Lewei_Link[] = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
////static const char Lewei_Head[] = "POST /api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
////static const char Lewei_Usek[] = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
////static const char Lewei_Host[] = "Host: www.lewei50.com\r\n";
//static const char Lewei_Head[] = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\nuserkey: 4a7c908d0de946de96e041dd84834154\r\nHost: www.lewei50.com\r\n";
//static const char Lewei_LenA[] = "Content-Length: ";
//static const char Lewei_LenB[] = "\r\n";
////static const char Lewei_Type[] = "Content-Type: text/html\r\n";
////static const char Lewei_Clos[] = "Connection: close\r\n\r\n";
//static const char Lewei_JsnA[] = "[{\"Name\":\"WDLD\",\"Value\":\"";
//static const char Lewei_JsnB[] = "\"}]";
//-------------------------------------------------------------------------
//static String Lewei_Post = "";
static String Lewei_Data = "";
//-------------------------------------------------------------------------

String myBuffer = "";
void Lewei_Loop() {
  lgln(F("Lewei_Loop..."));
  Serial.println(GetBuffer(Lewei_Link));

  //  //-------------------------------------------------------------------------------
  //  Lewei_Data = String( &(Lewei_JsnA));// + String(GetMyCupTemperature()) + &(Lewei_JsnB);
  //  int dn = &Lewei_Data.length();
  //  int tn = String(&Lewei_Head).length()
  //           + String(&Lewei_LenA).length() + String(dn).length() + String(&Lewei_LenB).length()
  //           + String("\r\n").length() + String(&Lewei_Data).length() + String("\r\n").length();
  //  senx = String(AT_Send) + String( tn + String(tn).length() ); lgln(senx);
  //  //-------------------------------------------------------------------------------
  //  wifiRun = wfs_cmd_back(Lewei_Link, AT_Cnet, AT_Errs, 2000 );
  //  wifiRun = wfs_cmd_back(senx, AT_Stat, AT_Errs, 2000 );
  //
  //  wfs.print(Lewei_Head);
  //  wfs.print(Lewei_LenA); wfs.print(dn); wfs.print(Lewei_LenB);
  //  wfs.print("\r\n"); wfs.print(Lewei_Data); wfs.print("\r\n");
  //  wifiRun = wfs_cmd_back("\r\n", AT_Clsd, AT_Empt, 20000);

}
String GetBuffer(const char x[]) {
  myBuffer = "";
  char myChar;
  int len = strlen_P(x);
  for (int k = 0; k < len; k++) {
    myChar =  pgm_read_byte_near(x + k);
    myBuffer += myChar;
  }
  return myBuffer;
}
//-------------------------------------------------------------------------
