#include <uarlWIFI.h>
WIFI wifi;
void setup()
{
  Serial.begin(9600);
  Serial.println("begin(9600)");
  
  bool b = wifi.Initialize(STA, "acDev", "AbroadCar2015()",1,3);
  if (!b)
  {
    Serial.println("Init error");
  }else{
    Serial.println("Init done..");
  }
  
  wifi.ipConfig(UDP, "172.16.102.60", 8888);
  Serial.println("setup done..");
  wifi.SendMessage("setup done..");

  pinMode(13, OUTPUT);
}
void loop()
{
  //定一个接收消息用的buffer
  char buf[1024];
  int iLen = wifi.ReceiveMessage(buf);
  if (iLen > 0)
  {
    //判断buf是否为规定字符串
    if (strcmp(buf, "HIGH") == 0)
    {
      digitalWrite(13, HIGH);
    }
    else if (strcmp(buf, "LOW") == 0)
    {
      digitalWrite(13, LOW);
    }
  }
}
