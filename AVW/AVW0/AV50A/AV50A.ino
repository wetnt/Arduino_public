#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial myAvw(A0, A1);//RX,TX

void setup() {
  //--------------------------------------- 
  Serial.begin(115200);
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
  SerialShow();
  BBKLcd_Loop();
  LEWEI_Loop();
  //---------------------------------------  
  delay(1000);
  //---------------------------------------  
}
