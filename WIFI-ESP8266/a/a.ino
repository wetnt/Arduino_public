/*show you home wifi AP*/
//#include <uarlWIFI_328.h>
#include <uarlWIFI.h>

String ssid ="MMMM";
String pwd = "1234567890123";
bool b = false; 
WIFI wifi;
void setup() {
  
  Serial.begin(9600);
  delay(2000);
  Serial.print("Initialize.....");
  //b = wifi.Initialize(1,ssid,pwd,1,2);
  Serial.println(b);
  Serial.print("confMode.....");
  //b = wifi.confMode(1);  // STA or  AP or  AP+STA
  Serial.println(b);
  //Serial.print("Reset.....");
  //wifi.Reset();
  Serial.println(b);
  Serial.print("showAP.....");
  //返回wifi列表
  Serial.println(wifi.showAP());
  
  Serial.println("confJAP.....");
  //配置登陆wifi接入点
  wifi.confJAP(ssid,pwd);
  
  Serial.println("showJAP.....");
  //返回目前连接的wifi接入点信息
  Serial.println(wifi.showJAP());
  
  Serial.println("showSAP.....");
  //显示ap模式下的模块的ssid 密码 通道号 以及加密方式
  Serial.println(wifi.showSAP());
  
  Serial.println("showIP.....");
  //显示本机目前获取的ip地址
  Serial.println(wifi.showIP());
}
void loop() {
 
}
