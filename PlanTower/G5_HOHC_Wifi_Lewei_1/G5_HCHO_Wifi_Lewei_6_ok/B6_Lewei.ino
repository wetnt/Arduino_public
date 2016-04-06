//-------------------------------------------------------------------------
const static char Lewei_Link[] PROGMEM = {"AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80"};
const static char Lewei_Head[] PROGMEM = {"POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n"};
const static char Lewei_Usek[] PROGMEM = {"userkey: 4a7c908d0de946de96e041dd84834154\r\n"};
const static char Lewei_Host[] PROGMEM = {"Host: www.lewei50.com\r\n"};
const static char Lewei_LenA[] PROGMEM = {"Content-Length: "};
const static char Lewei_LenB[] PROGMEM = {"\r\n"};
const static char Lewei_Type[] PROGMEM = {"Content-Type: application/x-www-form-urlencoded\r\n"};
const static char Lewei_Clos[] PROGMEM = {"Connection: close\r\n"};
//-------------------------------------------------------------------
const static char Lewei_JsnA[] PROGMEM = {"{\"Name\":\""};
const static char Lewei_JsnB[] PROGMEM = {"\",\"Value\":\""};
const static char Lewei_JsnC[] PROGMEM = {"\"}"};
//-------------------------------------------------------------------
const static char Lewei_Line[] PROGMEM = {"\r\n"};
//static char Lewei_Date[] = "Date:";
//static char Lewei_Gmts[] = "GMT";
//-------------------------------------------------------------------------
static String Lewei_Data = "";
//-------------------------------------------------------------------------
String Lewei_Build() {
  String s = "";
  s += Lewei_Json("WD", String(Si_Temperature)) + ',';
  s += Lewei_Json("SD", String(Si_Humidity)) + ',';
  s += Lewei_Json("JQ", String(fHCHO)) + ',';
  s += Lewei_Json("PM", String(g.cf25));
  s = "[" + s + "]"; //lgln(s);
  return s;
}
String Lewei_Json(String nameStr, String valueStr) {
  return S(Lewei_JsnA) + nameStr + S(Lewei_JsnB) + valueStr + S(Lewei_JsnC);
}
void Lewei_Loop() {
  //-------------------------------------------------------------------------------
  Lewei_Data = Lewei_Build();
  int dn = Lewei_Data.length();
  int tn = L(Lewei_Head) + L(Lewei_Usek) + L(Lewei_Host)
           + L(Lewei_LenA) + String(dn).length() + L(Lewei_LenB)
           + L(Lewei_Clos) + L(Lewei_Line)
           + Lewei_Data.length() + L(Lewei_Line) + L(Lewei_Line);
  senx = S(AT_Send) + String( tn + String(tn).length() );
  String sendStr = "";
  sendStr += S(Lewei_Head) + S(Lewei_Usek) + S(Lewei_Host);
  sendStr += S(Lewei_LenA) + String(dn) + S(Lewei_LenB);
  sendStr += S(Lewei_Clos) + S(Lewei_Line);
  sendStr += Lewei_Data + S(Lewei_Line) + S(Lewei_Line);
  //-------------------------------------------------------------------------------
  wifiRun = wfs_cmd_back(S(Lewei_Link), S(AT_Cnet), S(AT_Errs), 2000 );
  wifiRun = wfs_cmd_back(senx,          S(AT_Stat), S(AT_Errs), 2000 );  
  //lgln(sendStr);
  wifiRun = wfs_cmd_backAB(sendStr, "Date: ", "GMT", 5000); wfs_serial_clear();
  //wifiRun = wfs_cmd_backAB(sendStr, "Successful", "}", 5000); wfs_serial_clear();
  //-------------------------------------------------------------------------------
  lgln(wifiBack);
  //-------------------------------------------------------------------------------
}
//=============================================================================================
