//=========================================================================
#include <SoftwareSerial.h>
SoftwareSerial ss(10, 11); // RX, TX
static const long GasBaud = 9600;
boolean logKey = false;
String ssBuffer = "";
//=========================================================================
void ss_setup(boolean lgKey) {
  ss.begin(GasBaud); lg(F("BT.Serial.start! = ")); lg(GasBaud); lg();
  logKey = lgKey;
}
void ss_loop() {
  while (ss.available() > 0) {
    char c = ss.read();
    if (logKey) lg(c);
    ssBuffer += c;
    if (c == '\r') {
      lg(ssBuffer); lg();
      Morse_String_Run(ssBuffer);
      ssBuffer = "";
    }
  }
}
//=========================================================================
typedef struct charCheckSave {
  int len = 0, inx = 0;
  String str = "";
  void init(String s) {
    str = String(s); inx = 0;
    len = s.length();
    //lg("check=");lg(len); lg();
  }
  boolean check(char c) {
    //lg("="); lg(c); lg("="); lg(inx); lg();
    if (len == 0) return false;
    if (inx == len - 1) {
      inx = 0; return true;
    }
    if (str[inx] == c) inx++; else inx = 0;
    return false;
  }
} charCheckSave;
//=========================================================================
charCheckSave ck1, ck2;
//=========================================================================
void ss_clear() {
  while (ss.available() > 0) {
    char c = ss.read();
    if (logKey) lg(c);
  }
}
boolean ss_send(String comStr) {
  ss_clear(); ss.println(comStr);
  if (logKey) lg(comStr);
  return true;
}
boolean ss_send_YN(String comStr, String strOK, String strNO, long timeout) { //
  //-------------------------------------------------------
  char c; unsigned long start = millis(); ssBuffer = "";
  ck1.init(strOK); ck2.init(strNO);
  ss_clear(); ss.println(comStr);
  //-------------------------------------------------------
  while (millis() - start < timeout) {
    while (ss.available() > 0) {
      c = ss.read();
      if (c == '\0') continue;
      if (logKey) lg(c);
      ssBuffer += c;
      if (ck1.check(c)) return true;
      if (ck2.check(c)) return false;
    }
  }
  return false;
  //-------------------------------------------------------
}
boolean ss_send_back_AB(String comStr, String strA, String strB, long timeout) { //get back Str from A to B
  //-------------------------------------------------------
  boolean save = false; char c; unsigned long start = millis(); ssBuffer = "";
  ck1.init(strA);  ck2.init(strB); ss_clear(); ss.println(comStr);
  //-------------------------------------------------------
  while (millis() - start < timeout) {
    while (ss.available() > 0) {
      //-----------------------------------
      c = ss.read();
      if (c == '\0') continue;
      if (logKey) lg(c);
      //-----------------------------------
      if (save) ssBuffer += c;
      if (ck1.check(c)) save = true;
      if (ck2.check(c)) save = false;
      //-----------------------------------
    }
  }
  //-------------------------------------------------------
  return false;
  //-------------------------------------------------------
}
//=========================================================================
