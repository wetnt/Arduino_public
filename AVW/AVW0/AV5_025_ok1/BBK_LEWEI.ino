//===============================================================
#include <LiquidCrystal.h>
//===============================================================
#define USERKEY          "4a7c908d0de946de96e041dd84834154" // BOBOKing_Lewei_ID
#define LW_GATEWAY       "01" // BOBOKing_Lewei_GAT
char server[] = "open.lewei50.com";
//===============================================================
void LEWEI_Setup(){
  Serial.print("LEWEI_Setup......"); 
  LeWeiClient(USERKEY,LW_GATEWAY);
  Serial.println("OK"); 
}
void LEWEI_Loop(){
  //---------------------------------------
  LeWeiClientAppend("YDL", Kwhs);
  LeWeiClientAppend("GL", Watt);
  LeWeiClientAppend("DL", Amps); 
  LeWeiClientAppend("DY", Volt); 
  LeWeiClientAppend("GLYS", Pfss);
  //---------------------------------------
  LeWeiClientAppend("WD", DHT_WD); 
  LeWeiClientAppend("SD", DHT_SD); 
  //---------------------------------------     
  LeWeiClientSend();
  //---------------------------------------
}
//===============================================================
char head[160];
char * user_data;
int user_str_length;
bool begin,end;
EthernetClient client;
//===============================================================
void LeWeiClient(const char * user_key, const char * gateway)
{
  //----------------------------------------------------
  char *ptr = head;
  int head_length = 0;
  int tmp;
  //----------------------------------------------------
  user_data = NULL;
  user_str_length = 0;
  //----------------------------------------------------
  begin = false;
  end = false;
  //----------------------------------------------------
  // build head.
  tmp = sprintf(ptr,
  "POST /api/V1/Gateway/UpdateSensors/%s HTTP/1.1\r\n",
  gateway);
  head_length += tmp;
  ptr += tmp;
  //----------------------------------------------------
  // build userkey.
  tmp = sprintf(ptr,
  "userkey: %s\r\n",
  user_key);
  head_length += tmp;
  ptr += tmp;
  //----------------------------------------------------
  // build Host.
  tmp = sprintf(ptr, "Host: open.lewei50.com \r\n");
  head_length += tmp;
  ptr += tmp;
  //----------------------------------------------------
  // build User-Agent.
  tmp = sprintf(ptr, "User-Agent: RT-Thread ART\r\n");
  head_length += tmp;
  ptr += tmp;
  //----------------------------------------------------
}
int LeWeiClientAppend(const char * name, int value)
{  
  //----------------------------------------------------
  int length,tmp;
  char * ptr;
  //----------------------------------------------------
  if(begin == false)
  {
    user_data = (char *)malloc(2);
    if(user_data == NULL)
      return -1;
    //----------------------------------------------------
    user_data[0] = '[';
    user_data[1] = 0;
    user_str_length = 1;
    //----------------------------------------------------
    begin = true;
  }
  //----------------------------------------------------
  if(user_data == NULL)
    return -1;
  //----------------------------------------------------
  length  = 23; /* >>{"Name":"","Value":""},<< */
  length += 8;  /* name */
  length += 10; /* value */
  //----------------------------------------------------
  ptr = (char *)realloc(user_data, user_str_length + length + 1);
  if(ptr == NULL)
    return -1;
  user_data = ptr;
  //----------------------------------------------------
  ptr = user_data + user_str_length;
  length = sprintf(ptr,
  "{\"Name\":\"%s\",\"Value\":\"%d\"},",
  name,
  value);
  //----------------------------------------------------
  user_str_length += length;
  //DEBUG_PRINTF("append:%s\r\n", ptr);
  //----------------------------------------------------
}

int LeWeiClientAppend(const char * name, double value)
{
  //----------------------------------------------------
  int length,tmp;
  char * ptr;
  //----------------------------------------------------
  if(begin == false)
  {
    user_data = (char *)malloc(2);
    if(user_data == NULL)
      return -1;
    //----------------------------------------------------
    user_data[0] = '[';
    user_data[1] = 0;
    user_str_length = 1;
    //----------------------------------------------------
    begin = true;
    //----------------------------------------------------
  }
  //----------------------------------------------------
  if(user_data == NULL)
    return -1;
  //----------------------------------------------------
  length  = 23; /* >>{"Name":"","Value":""},<< */
  length += 8;  /* name */
  length += 20; /* value: ab.cd */
  //----------------------------------------------------
  ptr = (char *)realloc(user_data, user_str_length + length + 1);
  if(ptr == NULL)
    return -1;
  user_data = ptr; 
  //----------------------------------------------------
  "", 
  //----------------------------------------------------
  ptr = user_data + user_str_length;
  length = sprintf(ptr,
  "{\"Name\":\"%s\",\"Value\":\"%d.%02u\"},",
  name,
  (int)value, (long)(abs(value)*100+0.5) % 100);
  //----------------------------------------------------
  user_str_length += length;
  //DEBUG_PRINTF("append:%s\r\n", ptr);
  //----------------------------------------------------
}

int LeWeiClientSend()
{
  //----------------------------------------------------
  int result = 0;
  //----------------------------------------------------
  if (client.connect(server, 80))
  {
    // send the HTTP PUT request:
    client.print(head);
    //----------------------------------------------------
    client.print("Content-Length: ");
    client.println(strlen(user_data) + 1); // ']'
    //----------------------------------------------------
    // last pieces of the HTTP PUT request:
    client.println("Connection: close");
    client.println();
    //----------------------------------------------------
    // post data
    client.print(user_data);
    client.println("]");
    //----------------------------------------------------
    //DEBUG_PRINTF("data:%s]\r\n", user_data);
    //----------------------------------------------------
    result = 0;
    //----------------------------------------------------
    goto send_exit;
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
  client.stop();
  //----------------------------------------------------
  begin = false;
  end = false;
  //----------------------------------------------------
  if(user_data != NULL)
    free(user_data);
  //----------------------------------------------------
  return result;
  //----------------------------------------------------
}
