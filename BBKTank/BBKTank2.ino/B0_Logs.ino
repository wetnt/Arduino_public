//===================================================================
#define  lgs  Serial
static const long LGSBaud = 115200;
//===================================================================
void lgsetup(String s) {
  lgs.begin(LGSBaud); delay(200);
  lgln(s); lgln(F("Log.Serial.start!"));
}
//===================================================================
void lg(String str) {
  lgs.print(str);
}
void lg(int s) {
  lgs.print(s);
}
void lg(unsigned int s) {
  lgs.print(s);
}
void lg(double s) {
  lgs.print(s);
}
void lg(float s) {
  lgs.print(s);
}
void lg(long s) {
  lgs.print(s);
}
void lg(unsigned long s) {
  lgs.print(s);
}
void lg(char s) {
  lgs.print(s);
}
void lgln(String str) {
  lg(str);
  lgs.println("");
}
void lg() {
  lgs.println("");
}
//===================================================================
void lgFeed() {
  //----------------------------------------------------------
  while (lgs.available()) {
    char c = lgs.read();
    rc_cmd_feed(c);
    lg(c);
  }
  //----------------------------------------------------------
}

