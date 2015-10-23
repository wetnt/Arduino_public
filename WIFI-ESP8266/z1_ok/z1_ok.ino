//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial gas(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 9600;
//-------------------------------------------------------------------------
String txt = "";
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  gas.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  netStart();
}
void loop() {
  //-------------------------------
  //gasLoop();
  //lgsLoop();
  NetLoop();
  smartDelay(10000);
  //-------------------------------
}
void gasLoop() {
  //-------------------------------
  while (gas.available()) {
    char c = gas.read();
    lgs.write(c);
    //HCHOCheck(c);
  }
  //-------------------------------
}
void lgsLoop() {
  //-------------------------------
  while (lgs.available()) {
    char c = lgs.read();
    gas.write(c);
    //HCHOCheck(c);
  }
  //-------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    gasLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

