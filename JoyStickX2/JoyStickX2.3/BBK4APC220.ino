//===================================================================
#include <SoftwareSerial.h>
//===================================================================
//===================================================================
//#define  apcTR  Serial2
SoftwareSerial apcTR(10, 11); //RX,TX
static const int APCBaud = 9600;
//===================================================================
void APC220_setup() {
  apcTR.begin(APCBaud);
  lgln(F("APC.Serial.start!"));
}
static void APC220_Feed() {
  //-------------------------------
  apcTR.listen();
  while (apcTR.available()) {
    char c = apcTR.read();
    JoyExpChar(c);
    //GpsLineFeed(c);
    //lgs.write(c);
  }
  //-------------------------------
}
static void APC220_Send(char chars[], boolean lnKey) {
  apcTR.print(chars);
  if (lnKey) apcTR.println();
}
static void APC220_Send(String str, boolean lnKey) {
  apcTR.print(str);
  if (lnKey) apcTR.println();
}
//===================================================================
