//===================================================================
#include <SoftwareSerial.h>
//SoftwareSerial ss(D2, D1);
SoftwareSerial ss(D2, D1, false, 256);
long ss_Baud = 9600;
boolean logKey = false;
//===================================================================
void ss8266_init(String ss_name, long btl, boolean lgKey) {
  logKey = lgKey; ss_Baud = btl;
  ss.begin(btl); delay(200);
  lg(ss_name); lg(F(".start = ")); lg(ss_Baud); lg();
}
//===================================================================
void ss_feed() {
  //lg(ss.available());
  while (ss.available()) {
    char c = ss.read();
    if (logKey) lg(c);
  }
}
//===================================================================
void ss_write() {
  ss.println("sad");
}
//===================================================================
