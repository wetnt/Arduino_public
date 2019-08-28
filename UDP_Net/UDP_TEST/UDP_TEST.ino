//--------------------------------------------------
#include <WiFi.h>
#include <WiFiClient.h>
#include "SSD1306.h"
SSD1306  display(0x3c, 4, 15);
//--------------------------------------------------
//const char* ssid     = "MMMM";
//const char* password = "1234567890123";
//--------------------------------------------------
const char* ssid     = "JTFY";
const char* password = "jtfy2468";
//--------------------------------------------------
#include <WiFiUdp.h>
WiFiUDP Udp;
char incomingPacket[100];
//--------------------------------------------------
void setup() {
  //--------------------------------------------------
  lgsetup("UDP_Test"); lg(); lg();
  //--------------------------------------------------
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); delay(50);
  digitalWrite(16, HIGH); delay(50);
  //--------------------------------------------------
  lg("display.init()"); lg();
  display.init();
  //display.flipScreenVertically();
  display.setContrast(255);
  //--------------------------------------------------
  lg("display.UDP_Test"); lg();
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(10, 10, "UDP_Test");
  display.display();
  //--------------------------------------------------
  lg(ssid); lg();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    lg("."); delay(500);
  } lg();
  lg("WiFi connected.");
  lg("IP address: ");
  lg(WiFi.localIP());
  lg();
  //--------------------------------------------------
  lg("server.begin()"); lg();
  Udp.begin(38888);
  //--------------------------------------------------
}
void loop() {
  //--------------------------------------------------
  float f = random(0, 1000) / 100;
  float t = temperatureRead();
  //--------------------------------------------------
  display.clear();
  display.drawString(10,2, String(t));
  display.display();
  lg(t); lg();
  //--------------------------------------------------
  //--------------------------------------------------
  smartDelay(5 * 1000);
  //--------------------------------------------------
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    //lgFeed(); wfs_loop(); Dog_Loop();
    udploop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================

void udploop() {
  int packetSize = Udp.parsePacket(); //获取当前队首数据包长度
  if (packetSize) {                    // 有数据可用
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 100); // 读取数据到incomingPacket
    if (len > 0) {                             // 如果正确读取
      incomingPacket[len] = 0; //末尾补0结束字符串
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
      //--------------------------------------------------
      display.clear();
      display.drawString(0,10, String(incomingPacket));
      display.display();
      //--------------------------------------------------
      //      if (incomingPacket[0] == 0xfa && incomingPacket[4] == 0xfb) {
      //        if (incomingPacket[1] == 0x01) {
      //          Serial.printf("UDP speed: 0x%x\n", incomingPacket[2]);
      //          Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      //          Udp.write("sss");
      //          Udp.endPacket();
      //        }
      //      }else{ // 如果非指定消息
      //        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      //        Udp.write("Data Error!"); // 回复Data Error!
      //        Udp.endPacket();
      //      }
    }
  }
}
