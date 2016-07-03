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
void lg(float s, int n) {
  lgs.print(s, n);
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
//===================================================================
void lg() {
  lgs.println("");
}
void lt() {
  lgs.print("\t");
}
void lgln() {
  lgs.println("");
}
void lgln(String str) {
  lgs.print(str);
  lgs.println("");
}
void lgDigits(int d) {
  if (d < 10) lg('0');
  lg(d);
}
//===================================================================
void lgFeed() {
  //----------------------------------------------------------
  while (lgs.available()) {
    char c = lgs.read();
    //rc_cmd_loop(c);
    //lg(c);
  }
  //----------------------------------------------------------
}

