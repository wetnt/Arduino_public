//-------------------------------------------------------------------------
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
#define  wfs  Serial2
static const long LGSBaud = 9600;
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lgs.print(F("Log.Serial.start! = ")); lgs.print(LGSBaud); lgs.println("");
  wfs.begin(GasBaud); lgs.print(F("Gas.Serial.start! = ")); lgs.print(GasBaud); lgs.println("");
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
