//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial wfs(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 9600;
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  wfs.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  netStart();
  //netJoinAP("acDev","AbroadCar2015()");
}
void loop() {
  //-------------------------------
  NetLink_bbkgps_time();  
  NetExp_bbkgps_time();
  NetExp_bbkgps_show();
  smartDelay(10000);
  //-------------------------------
}
//-------------------------------------------------------------------------
bool bufferKey = false;
void wfsLoop() {
  while (wfs.available()) {
    //------------------------------------
    char c = wfs.read();
    lgs.write(c);
    if (bufferKey) { HttpBufferSave(c);  }
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
