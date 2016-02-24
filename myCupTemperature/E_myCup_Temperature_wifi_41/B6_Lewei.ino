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

static const char Lewei_Link[] = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
static const char Lewei_Head[] = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
static const char Lewei_Usek[] = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
static const char Lewei_Host[] = "Host: www.lewei50.com\r\n";
static const char Lewei_LenA[] = "Content-Length: ";
static const char Lewei_LenB[] = "\r\n";
//static const char Lewei_EndA[] = "Content-Type: application/x-www-form-urlencoded\r\n";
static const char Lewei_EndB[] = "Connection: close\r\n\r\n";
static const char Lewei_JsnA[] = "[{\"Name\":\"WDLD\",\"Value\":\"";
static const char Lewei_JsnB[] = "\"}]";
//-------------------------------------------------------------------------
//static String Lewei_Post = "";
static String Lewei_Data = "";
//-------------------------------------------------------------------------
void Lewei_Loop() {
  lgln(F("Lewei_Loop..."));
  NetLinkTestBaidu();
  return;
//
  Lewei_Data =  Lewei_JsnA + String(GetMyCupTemperature()) + Lewei_JsnB;
  int dn = Lewei_Data.length();

  String Lewei_Post = String(Lewei_Head) +
                      String(Lewei_Usek) +
                      String(Lewei_Host) +
                      String(Lewei_LenA) + String(dn) + String(Lewei_LenB) +
                      String(Lewei_Data) + "\r\n" +
                      //String(Lewei_EndA) +
                      String(Lewei_EndB);
  //lg("post="); lg(Lewei_Post); lg();
  HttpGetPost(Lewei_Link, Lewei_Post, 5);
  lg(wifiBack); lg('='); lg(wifiRun); lg();
}
//-------------------------------------------------------------------------
