//===================================================================
#include <SoftwareSerial.h>
SoftwareSerial ss(10, 11); // RX, TX
long ss_Baud = 9600;
boolean logKey = false;
//===================================================================
void ss_init(String ss_name, int rx, int tx, long btl, boolean lgKey) {
  logKey = lgKey; ss_Baud = btl;
  ss = SoftwareSerial(rx, tx);
  ss.begin(ss_Baud);delay(200);
  lg(ss_name); lg(F(".start = ")); lg(ss_Baud); lg();
}
//===================================================================
void ss_feed() {
  while (ss.available()) {
    byte c = ss.read();
    if (logKey) lg(c);
    G5Feed(c);
  }
}
//===================================================================
