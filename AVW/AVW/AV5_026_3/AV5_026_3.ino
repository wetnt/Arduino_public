//=====================================================
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>
//=====================================================
void setup() {
  //------------------------------------------
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("AVW5_Time_Start......");
  //------------------------------------------
  Time_Setup();   
  DHT_Setup();       
  Tube_Setup();
  LCD_Setup();  
  //------------------------------------------
  Ethernet_Setup();
  //------------------------------------------
  NTP_Setup();
  NTPTime_Get(true);
  NTPTime_Setting();
  NTPTime_Show();
  //---------------------------------------   
  AVW_Setup();  
  //LEWEI_Setup();
  //------------------------------------------
  Serial.println("Start_Loop......"); 
  //------------------------------------------
}
void loop() {
  //------------------------------------------
  Time_Loop(true);
  DHT_Loop(true);
  AVW_Loop(false);
  LCD_Loop(false);
  NTPTime_Loop(false);
  //LEWEI_Loop(true);
  //------------------------------------------
  Tube_Loop();//delay(2000);//数码管不能delay();
  //------------------------------------------
}

