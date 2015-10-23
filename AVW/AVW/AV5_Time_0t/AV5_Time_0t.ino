//=====================================================
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>
//=====================================================
#include "Timer.h"
Timer t; 
//------------------------------------------
void setup() {
  //------------------------------------------
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("AVW5_Time");
  //------------------------------------------
  DHT_Setup();  Serial.println("DHT_Setup");
  Tube_Setup();  Serial.println("Tube_Setup");
  LCD_Setup();  Serial.println("BBKLcd_Setup");
  //------------------------------------------
  Ethernet_Setup();  Serial.println("Ethernet_Setup");
  Ethernet_IPShow(); Serial.println("Ethernet_IPShow");
  //------------------------------------------
  NTP_Setup();    Serial.println("NTP_Setup");
  NTP_GetTime();  Serial.println("NTP_GetTime");
  //---------------------------------------   
  AVW_Setup();  Serial.println("AVW_Setup");
  //LEWEI_Setup();  Serial.println("LEWEI_Setup");
  //------------------------------------------
  //------------------------------------------
  int t1 = t.every(60000, NTP_GetTime);
  int t2 = t.every(1000, NTPTime_Show);
  int t3 = t.every(1000, DHT_Loop);
  int t4 = t.every(1000, AVW_Loop);
  int t5 = t.every(1000, LCD_Loop);
  //int t6 = t.every(1000, LEWEI_Loop);
  //------------------------------------------
}
void NTP_GetTime() {
  NTPTime_Loop(false);
  NTPTime_Show();
}
void loop() {
  //------------------------------------------
  t.update();
  Tube_Loop();
  //delay(2000);//数码管不能delay();
  //------------------------------------------
}

