//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial gas(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 115200;
//-------------------------------------------------------------------------
String txt = "";
String txx = "";
int ttt = 0;
bool ToneKey = false;
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg("Log.Serial.start! = "); lg(LGSBaud); lgln("");
  gas.begin(GasBaud); lg("Gas.Serial.start! = "); lg(GasBaud); lgln("");
  delay(2000);
  GpuClear();
  dshow();
}
//-------------------------------------------------------------------------
char HCHObuf[10];
int HCHOinx = 0;
void HCHOCheck(char c)
{
  if (c == '\n') {
    HCHOinx = 0;
    ToneKey = true;
  } else {
    ttt++;
    HCHObuf[HCHOinx] = c;
    HCHOinx++;
  }
}
void loop() {
  //-------------------------------
  ttt++;
  dshow();
  smartDelay(1000);
  //-------------------------------
}
void dshow() {
  String xxx = String(HCHObuf);
  txx = String("Ints = ") + ttt;
  txt = String("GetV = ") + xxx.toInt();
  ShowGPU(20, 0, "BOBOKing.Test.loop", 2);
  ShowGPU(20, 32, txx, 2);
  ShowGPU(20, 64, txt, 2);
  Serial.println("");
  if (ToneKey) {
    ToneKey = false;
    ToneStart();
  } else {
    ToneStops();
  }
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
void gasLoop() {
  //-------------------------------
  while (gas.available()) {
    char c = gas.read();
    HCHOCheck(c);
  }
  //-------------------------------
}
//-------------------------------------------------------------------------
void ShowHCHO()
{
  //txt = String("ABC:") + String(HCHObuf);
  txt = String(HCHObuf) + String("abc");
}
