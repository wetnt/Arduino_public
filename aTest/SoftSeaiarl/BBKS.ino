#include <SoftwareSerial.h>
SoftwareSerial ss(11, 10); // RX, TX
static const long ssBaud = 9600;
//-------------------------------------------------------------------------
String ssName = "ssName"; boolean logKey = false;
bool bufferKeys = false; String bufferBack = "";
char bufferStart = '+', bufferEnd = '}';
//=========================================================================
void ss_init(String ss_Name, boolean lgKey, char s, char e) {
  ssName = ss_Name; ss.begin(ssBaud);
  lg(ss_Name); lg(F(" start! = ")); lg(ssBaud); lg();
  logKey = lgKey; bufferBack = ""; sb_set(s, e);
}
void ss_loop() {
  while (ss.available()) {
    char c = ss.read();
    sb_save(c);
    if (logKey)lgs.write(c);
  }
}
void ss_send(String s) {
  ss.print(s);
}
void sb_set(char s, char e) {
  bufferStart = s; bufferEnd = e;
}
void sb_clear() {
  bufferBack = "";
}
void sb_save(char c) {
  if (c == bufferStart ) {
    bufferKeys = true;
    sb_clear();
  }
  if (bufferKeys) bufferBack += c;
  if (c == bufferEnd ) bufferKeys = false;
}
void sb_show() {
  lg(bufferBack);
}
//=========================================================================
