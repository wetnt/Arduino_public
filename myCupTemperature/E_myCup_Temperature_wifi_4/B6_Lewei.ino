//-------------------------------------------------------------------------
static String Lewei_Link = "AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80";
//static String Lewei_Keys = "4a7c908d0de946de96e041dd84834154";
//static String Lewei_PstH = "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n";
//static String Lewei_UseK = "userkey: 4a7c908d0de946de96e041dd84834154\r\n";
//static String Lewei_Host = "Host: www.lewei50.com\r\n";

#define REQ_PREFIX  ""\
  "POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n" \
//  "userkey: 4a7c908d0de946de96e041dd84834154\r\n" \
//  "Host: www.lewei50.com\r\n" \
//  "Accept: *" "/" "*\r\n" \
//  "Content-Length: "
#define REQ_SUFFIX  ""\
//  "\r\n" \
//  "Content-Type: application/x-www-form-urlencoded\r\n" \
//  "Connection: close\r\n\r\n"

//-------------------------------------------------------------------------
String Lewei_Post = "";
String Lewei_Data = "";
//-------------------------------------------------------------------------
int getDataN() {
  int n = String(REQ_PREFIX).length() +
          String(Lewei_Data.length()).length() +
          Lewei_Data.length() +
          String(REQ_SUFFIX).length();
  return n;
}

//-------------------------------------------------------------------------
//void GetLeweiPostString() {
//  Lewei_Post = Lewei_PstH;
//  Lewei_Post += Lewei_UseK;
//  Lewei_Post += Lewei_Host;
//  Lewei_Post += "Content-Length: " + String(Lewei_Data.length()) + "\r\n";
//  Lewei_Post += "\r\n";
//  Lewei_Post += Lewei_Data;
//  Lewei_Post += "\r\n";
//}
String Lewei_ValueJson() {
  float tx = GetMyCupTemperature();
  Lewei_Data = "[{\"Name\":\"WDLD\",\"Value\":\"" + String(tx) + "\"}]";
  return Lewei_Data;
}
//-------------------------------------------------------------------------
void Lewei_Loop() {
  Lewei_ValueJson();
  //GetLeweiPostString();
  HttpGetPost2(Lewei_Link, Lewei_Post, 5);
}
//-------------------------------------------------------------------------
