//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial wfs(9,8); //RX,TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 115200;
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg(F("Log.Serial.start! = ")); lg(LGSBaud); lgln("");
  wfs.begin(GasBaud); lg(F("Gas.Serial.start! = ")); lg(GasBaud); lgln("");
}

void loop() {
  smartDelay(10000);
}
void wfsLoop() {
  while (wfs.available()) {
    //------------------------------------
    char c = wfs.read();
    lgs.write(c);
    //------------------------------------
  }
}
void lgsLoop() {
  while (lgs.available()) {
    char c = lgs.read();
    wfs.write(c);
  }
}
//-------------------------------------------------------------------------
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    wfsLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
