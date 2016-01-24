//===================================================================
//#include <SoftwareSerial.h>
//SoftwareSerial rc(10, 11); //RX,TX
//===================================================================
#define rc Serial1
static const long RcBaud = 9600;
//===================================================================
void rc_setup() {
  rc.begin(RcBaud);
  lgln(F("RC.Serial1.start!"));
}
//===================================================================
void rcFeed() {
  //----------------------------------------------------------
  //apcTR.listen();
  while (rc.available()) {
    char c = rc.read();
    rc_cmd_loop(c);
  }
  //----------------------------------------------------------
}
static void rcSend(char chars[], boolean rnKey) {
  rc.print(chars);
  if (rnKey) rc.println();
}
static void rcSend(String str, boolean rnKey) {
  rc.print(str);
  if (rnKey) rc.println();
}
//===================================================================

