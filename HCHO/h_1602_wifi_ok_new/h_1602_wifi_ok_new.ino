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
void setup() {
  lgs.begin(LGSBaud); lg(F("Log.Serial.start! = ")); lg(LGSBaud); lgln(F(""));
  gas.begin(GasBaud); lg(F("Gas.Serial.start! = ")); lg(GasBaud); lgln(F(""));
  wfs.begin(WfsBaud); lg(F("Wfs.Serial.start! = ")); lg(WfsBaud); lgln(F(""));
  LCD1602_setup();
  LCD1602_Show(0, 0, F("SYS.Start!"));
  //netJoinAP(F("MMMM"),F("1234567890123"));
  DHT_setup();
  netStart();
}
int n = 0;
void loop() {
  //-------------------------------
  DHT_loop();
  AskHCHO();  smartDelayG(500);
  //-------------------------------
  LCD1602_Clear();  LcdHCHO();
  LCD1602_loop_test();
  //-------------------------------
  n++;
  if (n > 50) {
    n = 0;
    Lewei_Loop();
  }
  smartDelayW(500);
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
    gasLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
