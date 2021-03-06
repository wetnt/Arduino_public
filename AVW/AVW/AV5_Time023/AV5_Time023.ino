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
  Serial.println("AVW5_Time_Start......");
  //------------------------------------------
  Serial.println("Time_Setup......");     
  Time_Setup(); 
  Serial.println("DHT_Setup......");    
  DHT_Setup();
  Serial.println("Tube_Setup......");   
  Tube_Setup();  
  Serial.println("BBKLcd_Setup......");   
  LCD_Setup();  
  //------------------------------------------
  Serial.println("Ethernet_Setup");  
  Ethernet_Setup();  
  Serial.println("Ethernet_IPShow"); 
  Ethernet_IPShow(); 
  //------------------------------------------
  Serial.println("NTP_Setup");      
  NTP_Setup();    
  Serial.println("NTP_GetTime");    
  NTP_GetTime();
  //---------------------------------------   
  Serial.println("AVW_Setup");      
  AVW_Setup();  
  //Serial.println("LEWEI_Setup");    LEWEI_Setup();  
  //------------------------------------------
  //  int time_x0 = t.every(1000, Time_Loop);
  //  int time_x1 = t.every(1000, Time_Show);
  //  int t3 = t.every(1000, DHT_Loop);
  //  int t4 = t.every(1000, AVW_Loop);
  //  int t5 = t.every(1000, LCD_Loop);
  //int t6 = t.every(60000, NTP_GetTime);
  //int t7 = t.every(1000, LEWEI_Loop);
  //------------------------------------------
}
void NTP_GetTime() {
  NTPTime_Loop(false);
  NTPTime_Show();
}
void loop() {
  //------------------------------------------
  t.update();
  Tube_Loop();//delay(2000);//数码管不能delay();
  //------------------------------------------
}


