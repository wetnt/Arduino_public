//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
//SoftwareSerial wfs(10, 11); // RX, TX
SoftwareSerial wfs(8, 9); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 9600;
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  wfs.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  netStart();
  //netJoinAP(F("MMMM"),F("1234567890123"));
  //netJoinAP("acDev","AbroadCar2015()");
  DHT_setup();
}
int n = 0;
void loop() {
  //-------------------------------
  DHT_loop();
  //-------------------------------
  n++;
  if (n > 10) {
    n = 0;
    Lewei_Loop();
  }
  //-------------------------------
  smartDelay(1000);
  //-------------------------------
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void gasLoop() {
  while (wfs.available()) {
    char c = wfs.read();
    lgs.write(c);
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
    gasLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
