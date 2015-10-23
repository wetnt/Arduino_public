#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
//=====================================================
#include "Timer.h"
Timer t; 
//=====================================================
SoftwareSerial myAvw(A5,A3);//RX,TX

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
  //int t0 = t.every(1000, Time_Run); delay(123);  
  int t3 = t.every(10000, DHT_Loop);delay(123);  
  int t4 = t.every(1000, AVW_Loop);delay(123);  
  //int t5 = t.every(1000, BBKLcd_Loop);delay(123);  
  int t6 = t.every(1000, LEWEI_Loop);delay(123);  
  //--------------------------------------- 
}

void loop() {
  t.update();
//  //--------------------------------------- 
//  AVW_Loop();
//  DHT_Loop();
//  //---------------------------------------  
//  //SerialShow();
//  BBKLcd_Loop();
//  LEWEI_Loop();
//  //---------------------------------------  
//  delay(1000);
//  //---------------------------------------  
}
