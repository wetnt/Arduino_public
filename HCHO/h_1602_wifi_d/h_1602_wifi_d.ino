//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
//-------------------------------------------------------------------------
SoftwareSerial gas(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
SoftwareSerial wfs(9, 8); // RX, TX
static const long WfsBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 9600;
//-------------------------------------------------------------------------
String txt = "A.";
String tst = "B.";
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg(F("Log.Serial.start! = ")); lg(LGSBaud); lgln(F(""));
  gas.begin(GasBaud); lg(F("Gas.Serial.start! = ")); lg(GasBaud); lgln(F(""));
  wfs.begin(WfsBaud); lg(F("Wfs.Serial.start! = ")); lg(WfsBaud); lgln(F(""));
  netStart();
}
int n = 0;
void loop() {
  //-------------------------------
  n++;
  if (n > 15) {
    n = 0;
    Lewei_Loop();
  }
  smartDelay(1000);
  //-------------------------------
}
void gasLoop() {
  //-------------------------------
  while (gas.available()) {
    char c = gas.read();
    //HCHOCheck(c);
  }
  //-------------------------------
}
void lgsLoop() {
  //-------------------------------
  while (lgs.available()) {
    char c = lgs.read();
    //wfs.write(c);
  }
  //-------------------------------
}
void wfsLoop() {
  //-------------------------------
  while (wfs.available()) {
    char c = wfs.read();
    lgs.write(c);
  }
  //-------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    gasLoop();
    wfsLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
