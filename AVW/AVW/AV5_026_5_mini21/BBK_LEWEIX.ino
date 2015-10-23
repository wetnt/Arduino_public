//===============================================================
//#include <SPI.h>
//#include <Ethernet.h>
//#include <EthernetUdp.h>
//#include <Dns.h>
//===============================================================
void bugShow(String s){
  Serial.println(s);
}
//===============================================================
char server[] = "open.lewei50.com";
#define LW_GATEWAY	"01" // BOBOKing_Lewei_GAT
#define USERKEY		"4a7c908d0de946de96e041dd84834154" // BOBOKing_Lewei_ID
//===============================================================
EthernetClient LwClient;
long LwTime = millis(), LwTimeKey = 5*1000;
//===============================================================
void LeWei_Setup()
{
  //Serial.print("LeWei_Setup......"); 
  //BBK_LeWei_Client_Head(USERKEY,LW_GATEWAY);
  //Serial.println("OK"); 
  Serial.println("LeWei_Setup......OK"); 
}
void LeWei_Loop(bool showkey)
{
  //----------------------------------------------------
  if( millis() - LwTime < LwTimeKey) return; 
  LwTime = millis();
  //----------------------------------------------------
  BBK_LeWei_Client_Send();
  //----------------------------------------------------
}
//===============================================================
void BBK_LeWei_Client_Send()
{
  //----------------------------------------------------
  if (!LwClient.connect(server, 80)){ 
    LwClient.stop();
    Serial.println("LwClient Error!"); 
    return; 
  }
  //----------------------------------------------------
  LwClient.print("POST /api/V1/Gateway/UpdateSensors/");
  LwClient.print(LW_GATEWAY);
  LwClient.print(" HTTP/1.1");
  LwClient.print("\r\n");
  LwClient.print("userkey: ");
  LwClient.print(USERKEY);
  LwClient.print("\r\n");
  LwClient.print("Host: ");
  //LwClient.print("open.lewei50.com");
  LwClient.print(server);
  LwClient.print(" \r\n");
  LwClient.print("User-Agent: RT-Thread ART");
  LwClient.print("\r\n");
  //----------------------------------------------------
  int n = 180;//sData.length();
  Serial.print("n="); 
  Serial.println(n); 
  LwClient.print("Content-Length:");
  LwClient.print(n);
  LwClient.print(" \r\n");
  LwClient.print("Content-Type: application/x-www-form-urlencoded \r\n");
  LwClient.print("Connection: close \r\n");
  LwClient.print("\r\n");
  //----------------------------------------------------
  LwClient.print("[");
  LwClient.print("{\"Name\":\"WD\",\"Value\":\"");  LwClient.print(10);   LwClient.print("\"},");
  LwClient.print("{\"Name\":\"SD\",\"Value\":\"");  LwClient.print(50);   LwClient.print("\"},");
  LwClient.print("{\"Name\":\"DY\",\"Value\":\"");  LwClient.print(Volt); LwClient.print("\"},");
  LwClient.print("{\"Name\":\"DL\",\"Value\":\"");  LwClient.print(Amps); LwClient.print("\"},");
  LwClient.print("{\"Name\":\"GL\",\"Value\":\"");  LwClient.print(Watt); LwClient.print("\"},");
  LwClient.print("{\"Name\":\"YDL\",\"Value\":\""); LwClient.print(Kwhs); LwClient.print("\"},");
  LwClient.print("]");
  //----------------------------------------------------
  LwClient.stop();
  Serial.println("BBK_LeWei_Client_Send!"); 
  //----------------------------------------------------
}
//=========================================================================================
