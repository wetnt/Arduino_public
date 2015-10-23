//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial gas(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 115200;
//-------------------------------------------------------------------------
String txt = "ABC...";
String tst = "ABC...";
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  gas.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  LCD1602_setup();
  DHT_setup();
  LCD1602_Show(0,0,"SYS.Start!");
}
void loop() {
  //-------------------------------
  DHT_loop();
  AskHCHO();
  LCD1602_Clear();
  LCD1602_Show(0,0,txt);
  LCD1602_Show(5,1,tst);
  LCD1602_loop_test();
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
