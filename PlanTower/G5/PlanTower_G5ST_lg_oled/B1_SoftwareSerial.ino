//===================================================================
#include <SoftwareSerial.h>
SoftwareSerial ss(D7,D8); // RX, TX
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
  //lg("ss_feed()");
  while (ss.available()) {
    byte c = ss.read();
    if (logKey) lg(c);
    G5Feed(c);
  }
}
//===================================================================
