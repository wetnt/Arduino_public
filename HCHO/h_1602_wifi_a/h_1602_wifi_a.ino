//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
//-------------------------------------------------------------------------
SoftwareSerial gas(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
SoftwareSerial wfs(9,8); // RX, TX
static const long WfsBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 9600;
//-------------------------------------------------------------------------
//String txt = "ABC...";
//String tst = "ABC...";
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  gas.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  wfs.begin(WfsBaud); lg("Wfs.Serial.start! = "); lg(WfsBaud); lgln("");
  //DHT_setup();
}
void loop() {
  //-------------------------------
  AskHCHO();
  smartDelay(1000);
  //-------------------------------
}
void gasLoop() {
  //-------------------------------
  gas.listen();
  while (gas.available()) {
    char c = gas.read();
    HCHOCheck(c);
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
  wfs.listen();
  while (wfs.available()) {
    char c = wfs.read();
    //lgs.write(c);
  }
  //-------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    lgsLoop();
    gasLoop();
    wfsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
