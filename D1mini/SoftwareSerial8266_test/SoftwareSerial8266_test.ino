//===================================================================
#include <SoftwareSerial.h>
SoftwareSerial ss(D1,D2); // RX, TX
long ss_Baud = 9600;
boolean logKey = false;
//===================================================================
void ss_init(String ss_name, int rx, int tx, long btl, boolean lgKey) {
  logKey = lgKey; ss_Baud = btl;
  ss = SoftwareSerial(rx, tx);
  ss.begin(ss_Baud); delay(200);
  lg(ss_name); lg(F(".start "));
  lg(F("rx = ")); lg(rx); lg(F(" "));
  lg(F("rx = ")); lg(tx); lg(F(" "));
  lg(F(".baud = ")); lg(ss_Baud); lg();
}
//===================================================================
void ss_feed() {
  while (ss.available() > 0) {
    lg(ss.read());
  }
}
//===================================================================






//void loop() {
//  while (swSer.available() > 0) {
//    Serial.write(swSer.read());
//  }
//  while (Serial.available() > 0) {
//    swSer.write(Serial.read());
//  }
//
//}

static const String codeName = "PlanTowerG5_x_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  //ss_init(F("G5"), D1, D2, 9600, true); //String name, int rx, int tx, long btl, boolean lgKey
  //------------------------------------------------

  //ss = SoftwareSerial(D1,D2);
  ss.begin(ss_Baud); 
  
}
void loop() {
  ss_feed();
  delay(2);
}
