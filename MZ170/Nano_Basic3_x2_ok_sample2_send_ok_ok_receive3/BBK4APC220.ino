//===================================================================
#include <SoftwareSerial.h>
//===================================================================
//===================================================================
//#define  apcTR  Serial2
SoftwareSerial apcTR(8, 9); //RX,TX
static const int APCBaud = 9600;
//===================================================================
void APC220_setup() {
  apcTR.begin(APCBaud);
  lgln(F("APC.Serial.start!"));
}
static void APC220_Feed()
{
  //-------------------------------
  apcTR.listen();
  while (apcTR.available()) {
    char c = apcTR.read();
    GpsLineFeed(c);
    //lgs.write(c);
  }
  //-------------------------------
}
//===================================================================
