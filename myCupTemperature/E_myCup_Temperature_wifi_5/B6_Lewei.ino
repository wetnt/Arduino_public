//-------------------------------------------------------------------------
const static char Lewei_Link[] PROGMEM = {"AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80"};
const static char Lewei_Head[] PROGMEM = {"POST http://www.lewei50.com/api/V1/gateway/UpdateSensors/02 HTTP/1.1\r\n"};
const static char Lewei_Usek[] PROGMEM = {"userkey: 4a7c908d0de946de96e041dd84834154\r\n"};
const static char Lewei_Host[] PROGMEM = {"Host: www.lewei50.com\r\n"};
const static char Lewei_LenA[] PROGMEM = {"Content-Length: "};
const static char Lewei_LenB[] PROGMEM = {"\r\n"};
const static char Lewei_Type[] PROGMEM = {"Content-Type: application/x-www-form-urlencoded\r\n"};
const static char Lewei_Clos[] PROGMEM = {"Connection: close\r\n\r\n"};
const static char Lewei_JsnA[] PROGMEM = {"[{\"Name\":\"WDLD\",\"Value\":\""};
const static char Lewei_JsnB[] PROGMEM = {"\"}]"};
const static char Lewei_Line[] PROGMEM = {"\r\n"};
//-------------------------------------------------------------------------
static String Lewei_Data = "";
//-------------------------------------------------------------------------
void Lewei_Loop() {
  //-------------------------------------------------------------------------------
  //NetLinkTest_BBKGPS(); return;
  //-------------------------------------------------------------------------------
  float t = GetMyCupTemperature();
  //-------------------------------------------------------------------------------
  Lewei_Data = G(Lewei_JsnA) + String(t) + G(Lewei_JsnB);
  int dn = Lewei_Data.length();
  int tn = L(Lewei_Head) + L(Lewei_Usek) + L(Lewei_Host)
           + L(Lewei_LenA) + String(dn).length() + L(Lewei_LenB)
           + L(Lewei_Line) + Lewei_Data.length() + L(Lewei_Line)
           + L(Lewei_Clos) + L(Lewei_Line) + L(Lewei_Line);
  senx = G(AT_Send) + String( tn + String(tn).length() );//lgln(senx);
  //-------------------------------------------------------------------------------
  wifiRun = wfs_cmd_back(G(Lewei_Link), AT_Cnet, AT_Errs, 2000 );
  wifiRun = wfs_cmd_back(senx, AT_Stat, AT_Errs, 2000 );
  //-------------------------------------------------------------------------------
  wfs_cmd_send(G(Lewei_Head)); wfs_cmd_send(G(Lewei_Usek)); wfs_cmd_send(G(Lewei_Host));
  wfs_cmd_send(G(Lewei_LenA)); wfs_cmd_send(String(dn));    wfs_cmd_send(G(Lewei_LenB));
  wfs_cmd_send(G(Lewei_Line)); wfs_cmd_send(Lewei_Data);    wfs_cmd_send(G(Lewei_Line));
  wfs_cmd_send(G(Lewei_Clos)); wfs_cmd_send(G(Lewei_Line)); wfs_cmd_send(G(Lewei_Line));
  //wifiRun = wfs_cmd_back(G(Lewei_Line), AT_Clsd, AT_Empt, 20000);
  wifiRun = wfs_cmd_backAB(G(Lewei_Line), "+", "-", 5000);
  //-------------------------------------------------------------------------------
}
//=============================================================================================
