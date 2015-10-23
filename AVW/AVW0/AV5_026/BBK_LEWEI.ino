//===============================================================
//#include <SPI.h>
//#include <Ethernet.h>
//#include <EthernetUdp.h>
//#include <Dns.h>
//===============================================================
char server[] = "open.lewei50.com";
//#define LW_GATEWAY	"01" // BOBOKing_Lewei_GAT
//#define USERKEY		"4a7c908d0de946de96e041dd84834154" // BOBOKing_Lewei_ID
//===============================================================
long BBK_LeWei_Time = millis(), BBK_LeWei_TimeKey = 5*1000;
//===============================================================
void LEWEI_Setup()
{
  Serial.print("LEWEI_Setup......"); 
  //BBK_LeWei_Client_Head(USERKEY,LW_GATEWAY);
  Serial.println("OK"); 
}
void LEWEI_Loop(bool showkey)
{
  //---------------------------------------
  if( millis() - BBK_LeWei_Time < BBK_LeWei_TimeKey) return; 
  BBK_LeWei_Time = millis();
  //---------------------------------------
  int b = -1;
  //---------------------------------------
  b = BBK_LeWei_Client_Append();
  b = BBK_LeWei_Client_Append("GL", Watt);
  b = BBK_LeWei_Client_Append("DL", Amps);
  b = BBK_LeWei_Client_Append("DY", Volt);
  b = BBK_LeWei_Client_Append("YDL", Kwhs);
  b = BBK_LeWei_Client_Append("GLYS", Pfss);
  //---------------------------------------
  b = BBK_LeWei_Client_Append("WD", 20);
  b = BBK_LeWei_Client_Append("SD", 50.5f);
  //---------------------------------------
  b = BBK_LeWei_Client_Send(showkey);  
  //---------------------------------------
}
void BBK_LEWEI_DEBUG_Show(String s)
{
  Serial.println(s);
}
//===============================================================
char head[160];
char * user_data;
int user_str_length;
EthernetClient BBK_LeWei_Client;
//===============================================================
void BBK_LeWei_Client_Head(const char * user_key, const char * gateway)
{
  //----------------------------------------------------
  char *ptr = head;
  int head_length = 0;
  int tmp;
  //----------------------------------------------------
  user_data = NULL;
  user_str_length = 0;
  //----------------------------------------------------
  // build head.
  tmp = sprintf(
  ptr,
  "POST /api/V1/Gateway/UpdateSensors/%s HTTP/1.1\r\n",
  gateway
    );
  head_length += tmp; 
  ptr += tmp;
  //----------------------------------------------------
  // build userkey.
  tmp = sprintf(
  ptr,
  "userkey: %s\r\n",
  user_key
    );
  head_length += tmp; 
  ptr += tmp;
  //----------------------------------------------------
  // build Host.
  tmp = sprintf(
  ptr, 
  "Host: open.lewei50.com \r\n"
    );
  head_length += tmp; 
  ptr += tmp;
  //----------------------------------------------------
  // build User-Agent.
  tmp = sprintf(
  ptr, 
  "User-Agent: RT-Thread ART\r\n"
    );
  head_length += tmp; 
  ptr += tmp;
  //----------------------------------------------------
  //----------------------------------------------------
}
int BBK_LeWei_Client_Append()
{
  //----------------------------------------------------
  user_data = (char *)malloc(2);
  if(user_data == NULL){ 
    return -1; 
  }
  //----------------------------------------------------
  user_data[0] = '[';
  user_data[1] = 0;
  user_str_length = 1;
  //----------------------------------------------------
  if(user_data == NULL)
  { 
    return -1; 
  }
  else{
    return 0; 
  }
  //----------------------------------------------------
}
int BBK_LeWei_Client_Append(const char * name, int value)
{
  //----------------------------------------------------
  int length;
  char * ptr;
  //----------------------------------------------------
  length  = 23; /* >>{"Name":"","Value":""},<< */
  length += 8;  /* name */
  length += 10; /* value */
  //----------------------------------------------------
  ptr = (char *)realloc(user_data, user_str_length + length + 1);
  if(ptr == NULL) { 
    return -1; 
  }
  user_data = ptr;
  //----------------------------------------------------
  ptr = user_data + user_str_length;
  length = sprintf(
  ptr,
  "{\"Name\":\"%s\",\"Value\":\"%d\"},",
  name,
  value
    );
  user_str_length += length;
  //----------------------------------------------------
  //BBK_LEWEI_DEBUG_Show(ptr);
  //----------------------------------------------------
  return user_str_length;
  //----------------------------------------------------
}
int BBK_LeWei_Client_Append(const char * name, double value)
{
  //----------------------------------------------------
  int length;
  char * ptr;
  //----------------------------------------------------
  length  = 23; /* >>{"Name":"","Value":""},<< */
  length += 8;  /* name */
  length += 20; /* value: ab.cd */
  //----------------------------------------------------
  ptr = (char *)realloc(user_data, user_str_length + length + 1);
  if(ptr == NULL){ 
    return -1; 
  }
  //----------------------------------------------------
  user_data = ptr;
  ptr = user_data + user_str_length;
  //----------------------------------------------------
  length = sprintf(
  ptr,
  "{\"Name\":\"%s\",\"Value\":\"%d.%02u\"},",
  name,
  (int)value, (long)(abs(value)*100+0.5) % 100
    );
  user_str_length += length;
  //----------------------------------------------------
  //BBK_LEWEI_DEBUG_Show(ptr);
  //----------------------------------------------------
  return user_str_length;
  //----------------------------------------------------
}
int BBK_LeWei_Client_Send(bool showkey)
{
  //----------------------------------------------------
  int result = 0;
  int dataLength = 0;
  //----------------------------------------------------
  if (BBK_LeWei_Client.connect(server, 80))
  {    
    dataLength = strlen(user_data) + 1;
    //----------------------------------------------------
    BBK_LeWei_Client.print(head);// send the HTTP PUT request:
    BBK_LeWei_Client.print("Content-Length: ");
    BBK_LeWei_Client.println(dataLength); // '[]'
    //----------------------------------------------------
    // last pieces of the HTTP PUT request:
    BBK_LeWei_Client.println("Connection: close");
    BBK_LeWei_Client.println();
    //----------------------------------------------------
    //BBK_LeWei_Client.println("[");
    BBK_LeWei_Client.print(user_data);// post data
    BBK_LeWei_Client.println("]");
    //----------------------------------------------------
    result = 0;
    goto send_exit;
    //----------------------------------------------------
  }
  else
  {
    //----------------------------------------------------
    result = -1;
    goto send_exit;
    //----------------------------------------------------
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
    BBK_LEWEI_DEBUG_Show(head);
    BBK_LEWEI_DEBUG_Show("Content-Length: ");
    BBK_LEWEI_DEBUG_Show(String(dataLength));
    BBK_LEWEI_DEBUG_Show("Connection: close");
    //BBK_LEWEI_DEBUG_Show("");
    //BBK_LEWEI_DEBUG_Show("[");
    BBK_LEWEI_DEBUG_Show(user_data);
    BBK_LEWEI_DEBUG_Show("]");
    BBK_LEWEI_DEBUG_Show("result="+result);
  }
  //----------------------------------------------------
  return result;
  //----------------------------------------------------
}

