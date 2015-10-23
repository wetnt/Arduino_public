//===============================================================
char server[] = "open.lewei50.com";
#define LW_GATEWAY "01" // BOBOKing_Lewei_GAT
#define USERKEY    "4a7c908d0de946de96e041dd84834154" // BOBOKing_Lewei_ID
//===============================================================
EthernetClient LwClient;
long LwTime = millis(), LwTimeKey = 5*1000;
//===============================================================
void LeWei_Setup()
{
  Serial.println("LeWei_Setup......OK"); 
}
void LeWei_Loop(bool showkey)
{
  //----------------------------------------------------
  if( millis() - LwTime < LwTimeKey) return; 
  LwTime = millis();
  //----------------------------------------------------
  //"{\"Name\":\"%s\",\"Value\":\"%d.%02u\"},"
  //----------------------------------------------------
  String a = String("{\"Name\":\"");
  String b = String("\",\"Value\":\"");
  String c = String("\"},");
  //---------------------------------------------------------------------
  String d = String("[");
  //---------------------------------------------------------------------
  d.concat(a);d.concat("WD");d.concat(b);d.concat(20);d.concat(c);
  d.concat(a);d.concat("SD");d.concat(b);d.concat(30);d.concat(c);
  //---------------------------------------------------------------------
  d.concat(a);d.concat("DY");  d.concat(b);d.concat(Volt);d.concat(c);
  d.concat(a);d.concat("GL");  d.concat(b);d.concat(Watt);d.concat(c);
  d.concat(a);d.concat("DL");  d.concat(b);d.concat(Amps);d.concat(c);
  d.concat(a);d.concat("YDL"); d.concat(b);d.concat(Kwhs);d.concat(c);
  d.concat(a);d.concat("GLYS");d.concat(b);d.concat(Pfss);d.concat(c);
  //---------------------------------------------------------------------
  d.concat("]");
  //---------------------------------------------------------------------
  BBK_LeWei_Client_Send(d);
  //---------------------------------------------------------------------
}
//===============================================================
void BBK_LeWei_Client_Head(const char * user_key, const char * gateway)
{
  //----------------------------------------------------
  LwClient.print("POST /api/V1/Gateway/UpdateSensors/");
  LwClient.print(gateway);
  LwClient.print(" HTTP/1.1");
  LwClient.print("\r\n");
  LwClient.print("userkey: ");
  LwClient.print(user_key);
  LwClient.print("\r\n");
  LwClient.print("Host: ");
  LwClient.print(server);
  LwClient.print(" \r\n");
  LwClient.print("User-Agent: RT-Thread ART");
  LwClient.print("\r\n");
  //----------------------------------------------------
}
void BBK_LeWei_Client_Ends(String sData)
{
  //----------------------------------------------------
  LwClient.print("Content-Length:");
  LwClient.print(sData.length());
  LwClient.print(" \r\n");
  LwClient.print("Content-Type: application/x-www-form-urlencoded \r\n");
  LwClient.print("Connection: close \r\n");
  LwClient.print("\r\n");
  //----------------------------------------------------
}
void BBK_LeWei_Client_Send(String sData)
{
  //----------------------------------------------------
  if (!LwClient.connect(server, 80)){ 
    LwClient.stop();
    Serial.println("LwClient Error!"); 
    return; 
  }
  //----------------------------------------------------
  BBK_LeWei_Client_Head(USERKEY,LW_GATEWAY);
  BBK_LeWei_Client_Ends(sData);
  LwClient.println(sData);
  LwClient.stop();
  Serial.println(sData); 
  //Serial.println("BBK_LeWei_Client_Send!"); 
  //----------------------------------------------------
}
//=========================================================================================
