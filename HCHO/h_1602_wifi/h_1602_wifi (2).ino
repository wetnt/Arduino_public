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
String txt = "ABC...";
String tst = "ABC...";
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  gas.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  wfs.begin(WfsBaud); lg("Wfs.Serial.start! = "); lg(WfsBaud); lgln("");
  LCD1602_setup();
  LCD1602_Show(0, 0, "SYS.Start!");
  DHT_setup();
  netStart();
}
int n = 0;
void loop() {
  //-------------------------------
  DHT_loop();
  AskHCHO();
  LCD1602_Clear();
  LCD1602_Show(0, 0, txt);
  LCD1602_Show(5, 1, tst);
  LCD1602_loop_test();
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
