//=====================================================
#include <SPI.h>
#include <Ethernet.h>
//#include <EthernetUdp.h>
//#include <Dns.h>
//=====================================================
void setup() {
  //------------------------------------------
  Serial.begin(115200);
  while (!Serial){};
  Serial.println("AVW5_Start......");
  //------------------------------------------
  Time_Setup();   
  //DHT_Setup();       
  Tube_Setup();
  LCD_Setup();  
  //------------------------------------------
  Ethernet_Setup();
  //------------------------------------------
  NTP_Setup();
  //---------------------------------------   
  AVW_Setup();  
  LeWei_Setup();
  //------------------------------------------
  Serial.println("Start_Loop......"); 
  //------------------------------------------
  NTP_Get(true);
  //------------------------------------------
}
void loop() {
  //------------------------------------------
  Time_Loop(true);
  //DHT_Loop(true);
  AVW_Loop(false);
  //LCD_Loop(false);
  NTP_Loop(false);
  LeWei_Loop(true);
  //------------------------------------------
  Tube_Loop();//delay(2000);//数码管不能delay();
  //------------------------------------------
}




