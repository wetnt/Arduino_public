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
  //------------------------------------------
  Tube_Setup();
  LCD_Setup();
  //------------------------------------------
  Ethernet_Setup();
  Ethernet_IPShow(); 
  //------------------------------------------
  NTP_Setup();  
  NTP_GetTime();
  //------------------------------------------
  int t1 = t.every(6000, NTP_GetTime);
  int t2 = t.every(1000, LCD_Loop);
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

