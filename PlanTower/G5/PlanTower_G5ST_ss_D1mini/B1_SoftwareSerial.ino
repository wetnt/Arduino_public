//===================================================================
#include <SoftwareSerial.h>
SoftwareSerial ss(D1, D2); // RX, TX
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
void ss_init(String ss_name, boolean lgKey) {
  logKey = lgKey; delay(200);
  lg(ss_name); lg(F(".start "));
  lg(F(".baud = ")); lg(ss_Baud); lg();
}
//===================================================================
void ss_feed() {
  while (ss.available() > 0) {
    byte c = ss.read();
    if (logKey) lg(ss.read());
    G5Feed(c);
  }
}
//===================================================================
