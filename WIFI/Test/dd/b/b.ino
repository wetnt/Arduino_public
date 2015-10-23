/*show you home wifi AP*/
//#include <uarlWIFI_328.h>
#include <uarlWIFI.h>

String ssid ="MMMM";
String pwd = "1234567890123";
bool b = false; 
WIFI wifi;
void setup() {

  Serial.begin(9600);
  delay(1000);

  Serial.print("showAP.....");
  Serial.println(wifi.showAP());//返回wifi列表

  Serial.println("confJAP.....");  
  wifi.confJAP(ssid,pwd);//配置登陆wifi接入点

  Serial.println("showIP.....");
  //显示本机目前获取的ip地址
  Serial.println(wifi.showIP());

  Serial.println("showJAP.....");  
  Serial.println(wifi.showJAP());//wifi接入点信息

  Serial.println("showSAP.....");
  //显示ap模式下的模块的ssid 密码 通道号 以及加密方式
  Serial.println(wifi.showSAP());

  Serial.println("showIP.....");
  //显示本机目前获取的ip地址
  Serial.println(wifi.showIP());
}
void loop() {
  while (Serial1.available()>0)
  {
    char x = Serial1.read();  
    Serial.print(x);  
  }
}

