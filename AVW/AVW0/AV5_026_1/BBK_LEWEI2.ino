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
  LEWEI_Data  = "[";
  LEWEI_Data += String("{\"Name\":\"") + String("WD") + String("\",\"Value\":\"") + String(33.5) + String("\"},");
  LEWEI_Data += String("{\"Name\":\"") + String("SD") + String("\",\"Value\":\"") + String(50) + String("\"},");
  LEWEI_Data  = "]";
  //----------------------------------------------------
  b = BBK_LeWei_Client_Adds(LEWEI_Data);  
  b = BBK_LeWei_Client_Send(true);
  //----------------------------------------------------
}
void BBK_LEWEI_DEBUG_Show(String s)
{
  Serial.println(s);
}
//===============================================================
int dataLength = 0;
String lineEnd = String(" \r\n");
String LEWEI_Head = "",LEWEI_Body = "",LEWEI_Data = "";
//===============================================================
int BBK_LeWei_Client_Head(const char * user_key, const char * gateway)
{
  //----------------------------------------------------
  LEWEI_Head = "";
  LEWEI_Head += String("POST /api/V1/Gateway/UpdateSensors/") + String(gateway) + String(" HTTP/1.1") + lineEnd;
  LEWEI_Head += String("Host: open.lewei50.com") + lineEnd;
  LEWEI_Head += String("userkey: ") + String(user_key) + lineEnd;
  LEWEI_Head += String("User-Agent: RT-Thread ART") + lineEnd;
  //LEWEI_Head += String("Accept: */*") + lineEnd;
  //----------------------------------------------------
  return strlen(LEWEI_Head);
  //----------------------------------------------------
}
int BBK_LeWei_Client_Adds(String data)
{
  //----------------------------------------------------
  LEWEI_Body  = LEWEI_Head;
  //----------------------------------------------------
  dataLength = strlen(data);
  LEWEI_Body += String("Content-Length:") + String(dataLength) + lineEnd; 
  LEWEI_Body += String("Content-Type: application/x-www-form-urlencoded") + lineEnd; 
  LEWEI_Body += String("Connection: close") + lineEnd;
  LEWEI_Body += lineEnd;
  //----------------------------------------------------
  LEWEI_Body += data;
  //----------------------------------------------------
  return strlen(LEWEI_Body);
  //----------------------------------------------------
}
int BBK_LeWei_Client_Send(bool showkey)
{
  //----------------------------------------------------
  int result = 0;
  //----------------------------------------------------
  if (BBK_LeWei_Client.connect(server, 80))
  {
    BBK_LeWei_Client.println(LEWEI_Body);
    result = 0;
    goto send_exit;
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
  if(user_data != NULL){ 
    free(user_data); 
  }
  //----------------------------------------------------
  if(showkey){
    BBK_LEWEI_DEBUG_Show(LEWEI_Body);
    BBK_LEWEI_DEBUG_Show("result="+result);
  }
  //----------------------------------------------------
  return result;
  //----------------------------------------------------
}


int getLength(int someValue) {
	int digits = 1;
	int dividend = someValue / 10;
	while (dividend > 0) {
		dividend = dividend / 10;
		digits++;
	}
	return digits;
}

//=========================================================================================
//Serial.print("POST /v1.0/device/a030c5e8c64f4bcc90b5fc5788bc8bea/2/1/datapoints/add");
////a030c5e8c64f4bcc90b5fc5788bc8bea/2/1自己的device_id/device_value_id/device_type_id替代
//Serial.println("Host: api.machtalk.net");
//Serial.println("APIKey:7a19bd7874a541a6b4c50a831ea0b3b2"); //自己的替代
//Serial.print("Accept: *");
//Serial.print("/");
//Serial.println("*");
//Serial.println("Content-Length:");
//int thislength=17+getLength(sensorValue);
//Serial.println(thislength);
//Serial.println("Content-Type: application/x-www-form-urlencoded");
//Serial.println("Connection: close");
//Serial.println();
//Serial.print("params={\"value\":");
//Serial.print(sensorValue);
//Serial.println("}");
//=========================================================================================
