#include <LiquidCrystal.h>

//int preset_multiple_registers(int slave, int start_addr, int reg_count, int *data);
//int read_holding_registers(int slave, int start_addr, int count,int *dest, int dest_size);

void setup() {
  //--------------------------------------- 
  Serial.begin(4800);
  Serial.println("starttime");
  //--------------------------------------- 
  BBKLcd_Setup();
  Serial.println("BBKLcd_Setup");
  DHT_Setup();
  Serial.println("DHT_Setup");
  AVW_Setup();
  Serial.println("AVW_Setup");
  LEWEI_Setup();
  Serial.println("LEWEI_Setup");
  //--------------------------------------- 
}

void loop() {
  //--------------------------------------- 
  AVW_Loop();
  DHT_Loop();
  //---------------------------------------  
  //SerialShow();
  BBKLcd_Loop();
  LEWEI_Loop();
  //---------------------------------------  
  delay(1000);
  //---------------------------------------  
}
