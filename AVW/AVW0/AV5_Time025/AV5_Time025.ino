//=====================================================
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>
//=====================================================
//------------------------------------------
void setup() {
  //------------------------------------------
  Serial.begin(4800);
  while (!Serial) {
    ;
  }
  Serial.println("AVW5_Time_Start......");
  //------------------------------------------
  Serial.print("Time_Setup......");     Time_Setup(); 
  Serial.print("DHT_Setup......");      DHT_Setup();
  Serial.print("Tube_Setup......");     Tube_Setup();  
  Serial.print("BBKLcd_Setup......");   LCD_Setup();  
  //------------------------------------------
  Serial.print("Ethernet_Setup......");  Ethernet_Setup();  
  Serial.print("Ethernet_IPShow......"); Ethernet_IPShow(); 
  //------------------------------------------
  Serial.print("NTP_Setup......");       NTP_Setup();    
  Serial.print("NTP_GetTime......");     NTP_GetTime();
  //---------------------------------------   
  Serial.print("AVW_Setup......");      AVW_Setup();  
  //Serial.println("LEWEI_Setup");       LEWEI_Setup();  
  //------------------------------------------
  //int t0 = t.every(1000, Time_Run); delay(123);  
  //int t3 = t.every(10000, DHT_GetTH);delay(123);  
  int t4 = t.every(1000, AVW_Loop);delay(123);  
  int t5 = t.every(1000, LCD_AVW_Show);delay(123);  
  int t6 = t.every(6000, NTP_GetTime);delay(123);  
  //int t7 = t.every(1000, LEWEI_Loop);
  //------------------------------------------
  Serial.println("Start_Loop......"); 
  //------------------------------------------
}
void NTP_GetTime() {
  NTPTime_Loop(false);
  //NTPTime_Show();
}
void DHT_GetTH(){
  DHT_Loop();
  //DHT_Show();
}
void loop() {
  //------------------------------------------
  Time_Loop(true);
  DHT_Loop(true);
  //Tube_Loop();//delay(2000);//数码管不能delay();
  //------------------------------------------
}


