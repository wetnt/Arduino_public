#include <SoftwareSeriala.h>
#include <uarlWIFI.h>

SoftwareSerial mySerial(10,11);  //rx tx
WIFI wifi;

String ssid ="MMMM";
String pwd = "1234567890123";

void setup() {
  
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);
     
  String sss = String("AT+JoinAP=\"") + String(ssid)+ String("\",\"")+ String(pwd)+ String("\"");
  mySerial.println(sss);
  delay(5000);
  
  //Serial1.print("AT+JoinAP?");//所在网络的SSID
  //delay(1000);
  
  mySerial.print("AT+ShowIP");//模块目前的IP
  delay(5000);
  //Serial1.print("AT+MODE?");
  
 wifi.confMux(0);       //切换模块到单链接通讯模式
 wifi.Reset();           //切换模式必须重启后生效
 delay(5000);          //重启后一定要给足够的时间让模块获取IP
 wifi.newMux(UDP,"192.168.1.100",8080);    //建立一个连接 UPD 到我的电脑的8080端口 
 wifi.Send("hello Intelnet~!");                       //发送字符
 delay(1000);                                                   //等一会
 wifi.Send("My name is miniqiang");                //接着发字符
  
}
void loop() {
   while (mySerial.available()>0)
  {
    char x = mySerial.read();
    Serial.print(x);    
  }
}
