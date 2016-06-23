//===================================================================
#include <SoftwareSerial.h>
SoftwareSerial ss(10, 11); // RX, TX
long ss_Baud = 9600;
boolean logKey = false;
//===================================================================
void ss_init(String ss_name, int rx, int tx, long btl, boolean lgKey) {
  logKey = lgKey; ss_Baud = btl;
  ss = SoftwareSerial(rx, tx);
  ss.begin(ss_Baud); delay(200);
  lg(ss_name); lg(F(".start = ")); lg(ss_Baud); lg();
}
//===================================================================
void ss_feed() {
  while (ss.available()) {
    char c = ss.read();
    if (logKey) lg(c);
    TinyGPS_feed(c);
  }
}
//===================================================================
void sd(char s[]) {
  ss.print(s);
}
void sd(char s) {
  ss.print(s);
}
void sd(float s, int n) {
  ss.print(s, n);
}
void sd() {
  ss.println("");
}
//===================================================================
