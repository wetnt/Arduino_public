//===================================================================
#include <SoftwareSerial.h>
SoftwareSerial ss(D2, D1, false, 256);
//SoftwareSerial ss(10, 11); // RX, TX
long ss_Baud = 9600;
boolean logKey = false;
//===================================================================
void ss_init(String ss_name, int rx, int tx, long btl, boolean lgKey) {
  logKey = lgKey; ss_Baud = btl;
  ss = SoftwareSerial(rx, tx);
  ss.begin(btl);delay(200);
  lg(ss_name); lg(F(".start = ")); lg(ss_Baud); lg();
}
void ss8266_init(String ss_name, long btl, boolean lgKey) {
  logKey = lgKey; ss_Baud = btl;
  ss.begin(btl); delay(200);
  lg(ss_name); lg(F(".start = ")); lg(ss_Baud); lg();
}
//===================================================================
void ss_feed() {
  while (ss.available()) {
    char c = ss.read();
    lg(c);
    //if (logKey) lg(c);
    //G5Feed(c);
  }
}
//===================================================================
void ss_write(){
  ss.println("AT");
}
//===================================================================
