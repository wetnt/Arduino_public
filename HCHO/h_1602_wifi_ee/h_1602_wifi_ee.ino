//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
//-------------------------------------------------------------------------
SoftwareSerial wfs(9, 8); // RX, TX
static const long WfsBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 9600;
//-------------------------------------------------------------------------
//String txt = "A.";
//String tst = "B.";
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg(F("Log.Serial.start! = ")); lg(LGSBaud); lgln(F(""));
  wfs.begin(WfsBaud); lg(F("Wfs.Serial.start! = ")); lg(WfsBaud); lgln(F(""));

  //netJoinAP(F("MMMM"),F("1234567890123"));
  netStart();
}
int n = 0;
void loop() {
  //-------------------------------
  //-------------------------------
  //-------------------------------
  n++;
  if (n > 10) {
    n = 0;
    // Lewei_Loop();
  }
  smartDelayW(1000);
  //-------------------------------
}
void wfsLoop() {
  //-------------------------------
  wfs.listen();
  while (wfs.available()) {
    char c = wfs.read();
    lgs.write(c);
  }
  //-------------------------------
}
void lgsLoop() {
  //-------------------------------
  while (lgs.available()) {
    char c = lgs.read();
  }
  //-------------------------------
}
static void smartDelayW(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    wfsLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
static void smartDelayG(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    //gasLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
