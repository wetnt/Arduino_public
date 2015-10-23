#include <SoftwareSerial.h>
#define SSID        "MMMM"
#define PASS        "1234567890123"
#define DST_IP      "www.baidu.com" //"220.181.111.85"    //baidu.com
SoftwareSerial wifi(10, 11); // RX, TX
void setup()
{
  Serial.begin(9600);
  Serial.println("ESP8266 Demo");
  wifi.begin(9600);
  wifi.setTimeout(5000);

  //wifi.println("AT+RST");
  wifi.println("AT");
  delay(5000);
  if (wifi.find("OK"))
  {
    Serial.println("Module is ready");
  } else {
    Serial.println("Module have no response.");
    while (1);
  }
  delay(1000);
  //connect to the wifi
  boolean connected = false;
  for (int i = 0; i < 5; i++)  {
    if (connectWiFi())    {
      connected = true;
      break;
    }
  }
  if (!connected) {
    while (1);
  }
  delay(5000);


  wifi.println("AT+CIPMUX=0");
}
void loop()
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  wifi.println(cmd);
  Serial.println(cmd);
  if (wifi.find("Error")) return;
  cmd = "GET / HTTP/1.0\r\n\r\n";
  wifi.print("AT+CIPSEND=");
  wifi.println(cmd.length());

  Serial.println("AT+CIPSEND=");
  Serial.println(cmd.length());
  
  if (wifi.find(">"))
  {
    Serial.print(">");
  } else
  {
    wifi.println("AT+CIPCLOSE");
    Serial.println("connect timeout");
    delay(1000);
    return;
  }
  wifi.print(cmd);
  delay(2000);
  //wifi.find("+IPD");
  while (wifi.available())
  {
    char c = wifi.read();
    Serial.write(c);
    if (c == '\r') Serial.print('\n');
  }
  Serial.println("====");
  delay(1000);
}
boolean connectWiFi()
{
  wifi.println("AT+CWMODE=1");
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  Serial.println(cmd);
  wifi.println(cmd);
  delay(2000);
  if (wifi.find("OK"))
  {
    Serial.println("OK, Connected to WiFi.");
    return true;
  } else
  {
    Serial.println("Can not connect to the WiFi.");
    return false;
  }
}
