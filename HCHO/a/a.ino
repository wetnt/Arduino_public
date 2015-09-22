//------------------------------------------
static const long LGSBaud = 115200;
#define  lgs  Serial
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lgln(F("Log.Serial.start!"));
}

void loop() {
  //-------------------------------
  while (lgs.available()) {
    char c = lgs.read();
    HCHOCheck(c);
  }
  //-------------------------------
}


