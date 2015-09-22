//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial gas(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
static const long LGSBaud = 115200;
#define  lgs  Serial
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  gas.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
}
void loop() {
  //-------------------------------
  AskHCHO();
  smartDelay(2000);
  //-------------------------------
}
void gasLoop() {
  //-------------------------------
  while (gas.available()) {
    char c = gas.read();
    HCHOCheck(c);
  }
  //-------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    gasLoop();
    //-------------------------------
    while (lgs.available()) {
      gas.write(lgs.read());
    }
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
