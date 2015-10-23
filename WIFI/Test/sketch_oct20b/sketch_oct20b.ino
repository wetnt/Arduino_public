#include <uarlWIFI.h>
WIFI wifi;
bool b = false; 

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  Serial.print("confMux.....");
  wifi.confMux(0);       //切换模块到单链接通讯模式
 Serial.println(b);
 
 Serial.print("Reset.....");
 wifi.Reset();           //切换模式必须重启后生效
 Serial.println("Reset....."); 
 delay(5000);          //重启后一定要给足够的时间让模块获取IP
 Serial.println("Reset..5000...");
 
 Serial.println("newMux.....");
 wifi.newMux(UDP,"192.168.1.100",8080);    //建立一个连接 UPD 到我的电脑的8080端口 
 
 wifi.Send("hello Intelnet~!");                       //发送字符
 delay(1000);       //等一会
 wifi.Send("My name is miniqiang");                //接着发字符
 
}
void loop() {
 delay(1000);                                                   //等一会
 wifi.Send("My name is miniqiang");                //接着发字符
 Serial.println("name.....");
}

