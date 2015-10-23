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
}
void LeWei_Loop(bool showkey)
{
  //----------------------------------------------------
  if( millis() - LwTime < LwTimeKey) return; 
  LwTime = millis();
  //----------------------------------------------------
  //"{\"Name\":\"%s\",\"Value\":\"%d.%02u\"},"
  //----------------------------------------------------
  //d += "{\"Name\":\""+"WD"+"\",\"Value\":\""+ String(10) +String("\"}");
  //d += String("{\"Name\":\"")+String("WD")+String("\",\"Value\":\"")+ String(10) +String("\"}");
  //d += String("{\"Name\":\"")+String("SD")+String("\",\"Value\":\"")+ String(50) +String("\"}");
  //d += String("]");
  //----------------------------------------------------------------------------------------------------
  String d = String("[");
  //----------------------------------------------------------------------------------------------------
  //d.concat("{\"Name\":\"");d.concat("WD");d.concat("\",\"Value\":\"");d.concat(DHT_WD);d.concat("\"}");
  //d.concat("{\"Name\":\"");d.concat("SD");d.concat("\",\"Value\":\"");d.concat(DHT_SD);d.concat("\"}");
  //----------------------------------------------------------------------------------------------------
  d.concat("{\"Name\":\"");d.concat("DY");d.concat("\",\"Value\":\"");d.concat(Volt);d.concat("\"}");
  d.concat("{\"Name\":\"");d.concat("GL");d.concat("\",\"Value\":\"");d.concat(Watt);d.concat("\"}");
  d.concat("{\"Name\":\"");d.concat("DL");d.concat("\",\"Value\":\"");d.concat((int)Amps);d.concat("\"}");
  d.concat("{\"Name\":\"");d.concat("YDL");d.concat("\",\"Value\":\"");d.concat((int)Kwhs);d.concat("\"}");
  d.concat("{\"Name\":\"");d.concat("GLYS");d.concat("\",\"Value\":\"");d.concat((int)Pfss);d.concat("\"}");
  //----------------------------------------------------------------------------------------------------
  d.concat("]");
  //----------------------------------------------------------------------------------------------------
  BBK_LeWei_Client_Send(d);
  //----------------------------------------------------------------------------------------------------
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
  //LwClient.print("open.lewei50.com");
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
    return; 
  }
  //----------------------------------------------------
  BBK_LeWei_Client_Head(USERKEY,LW_GATEWAY);
  BBK_LeWei_Client_Ends(sData);
  LwClient.println(sData);
  LwClient.stop();
  //----------------------------------------------------
}
//=========================================================================================



