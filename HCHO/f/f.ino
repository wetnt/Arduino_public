//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial gas(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 115200;
//-------------------------------------------------------------------------
String txt = "";
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  gas.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  GpuClear();
}
void loop() {
  //-------------------------------
  AskHCHO();
  ShowGPU(20,20,txt,2);
  smartDelay(1000);
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
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
