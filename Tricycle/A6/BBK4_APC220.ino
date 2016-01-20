//===================================================================
//#include <SoftwareSerial.h>
//SoftwareSerial apcTR(10, 11); //RX,TX
//===================================================================
#define  apcTR  Serial1
static const int APCBaud = 9600;
//===================================================================
void APC220_setup() {
  apcTR.begin(APCBaud);
  lgln(F("APC.Serial.start!"));
}
static void APC220_Feed() {
  //-------------------------------
  //apcTR.listen();
  while (apcTR.available()) {
    char c = apcTR.read();
    rc_cmd_loop(c);
    lg(c);
  }
  //-------------------------------
}
static void APC220_Send(char chars[], boolean rnKey) {
  apcTR.print(chars);
  if (rnKey) apcTR.println();
}
static void APC220_Send(String str, boolean rnKey) {
  apcTR.print(str);
  if (rnKey) apcTR.println();
}
//===================================================================
