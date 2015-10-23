//===============================================================
//#include <SPI.h>
//#include <Ethernet.h>
//#include <EthernetUdp.h>
//#include <Dns.h>
//===============================================================
char server[] = "open.lewei50.com";
#define LW_GATEWAY	"01" // BOBOKing_Lewei_GAT
#define USERKEY		"4a7c908d0de946de96e041dd84834154" // BOBOKing_Lewei_ID
//===============================================================
EthernetClient BBK_LeWei_Client;
long BBK_LeWei_Time = millis(), BBK_LeWei_TimeKey = 5*1000;
//===============================================================
int dataLength = 0;
char  LEWEI_Head[160];
char  LEWEI_Ends[160];
char* LEWEI_Data;
//===============================================================
void BBK_LEWEI_DEBUG_Show(String s)
{
  Serial.println(s);
}
//===============================================================
void LEWEI_Setup()
{
  Serial.print("LEWEI_Setup......"); 
  BBK_LeWei_Client_Head(USERKEY,LW_GATEWAY);
  Serial.println("OK"); 
}
void LEWEI_Loop(bool showkey)
{
  //----------------------------------------------------
  if( millis() - BBK_LeWei_Time < BBK_LeWei_TimeKey) return; 
  BBK_LeWei_Time = millis();
  //----------------------------------------------------
  //"{\"Name\":\"%s\",\"Value\":\"%d.%02u\"},"
  //----------------------------------------------------
  if(LEWEI_Data == NULL){
    LEWEI_Data = (char *)malloc(1);
  }
  //----------------------------------------------------
  char *ptr = LEWEI_Data;
  sprintf(LEWEI_Data,"[");
  sprintf(LEWEI_Data,"{\"Name\":\"%s\",\"Value\":\"%d\"},","WD",10);
  sprintf(LEWEI_Data,"{\"Name\":\"%s\",\"Value\":\"%d\"},","SD",50);
  sprintf(LEWEI_Data,"]");
  //----------------------------------------------------
  BBK_LeWei_Client_Ends();
  BBK_LeWei_Client_Send();
  //----------------------------------------------------
}
//===============================================================
int BBK_LeWei_Client_Head(const char * user_key, const char * gateway)
{
  //----------------------------------------------------
  char *ptr = LEWEI_Head;
  sprintf(ptr,"POST /api/V1/Gateway/UpdateSensors/%s HTTP/1.1\r\n",gateway);
  sprintf(ptr,"userkey: %s\r\n",user_key);
  sprintf(ptr, "Host: open.lewei50.com \r\n");
  sprintf(ptr, "User-Agent: RT-Thread ART\r\n");
  //----------------------------------------------------
  return strlen(LEWEI_Head);
  //----------------------------------------------------
}
int BBK_LeWei_Client_Ends()
{
  //----------------------------------------------------
  dataLength = strlen(LEWEI_Data);
  //----------------------------------------------------
  char *ptr = LEWEI_Ends;
  sprintf(ptr,"Content-Length:%d \r\n",dataLength);
  sprintf(ptr,"Content-Type: application/x-www-form-urlencoded \r\n");
  sprintf(ptr,"Connection: close \r\n");
  sprintf(ptr,"\r\n");
  //----------------------------------------------------
  return strlen(LEWEI_Ends);
  //----------------------------------------------------
}
int BBK_LeWei_Client_Send()
{
  //----------------------------------------------------
  int result = 0;
  //----------------------------------------------------
  if (BBK_LeWei_Client.connect(server, 80))
  {
    //----------------------------------------------------    
    BBK_LeWei_Client.println(LEWEI_Head);
    BBK_LeWei_Client.println(LEWEI_Ends);
    BBK_LeWei_Client.println(LEWEI_Data);
    //----------------------------------------------------
    result = 0;
    goto send_exit;
    //----------------------------------------------------
  }
  else
  {
    result = -1;
    goto send_exit;
  }
  //----------------------------------------------------
send_exit:
  //----------------------------------------------------
  BBK_LeWei_Client.stop();
  //----------------------------------------------------
  if(LEWEI_Data != NULL){ 
    free(LEWEI_Ends); 
    free(LEWEI_Data); 
  }
  //----------------------------------------------------
  if(1){
    BBK_LEWEI_DEBUG_Show(LEWEI_Head);
    BBK_LEWEI_DEBUG_Show(LEWEI_Ends);
    BBK_LEWEI_DEBUG_Show(LEWEI_Data);
    BBK_LEWEI_DEBUG_Show("result="+result);
  }
  //----------------------------------------------------
  return result;
  //----------------------------------------------------
}
//=========================================================================================

