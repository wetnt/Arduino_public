//===================================================================
//#define  lgs  Serial
//static const long LGSBaud = 115200;
//===================================================================
void Log_setup() {
  lgs.begin(LGSBaud); 
  lgln(F("Log.Serial.start!"));
}
//===================================================================
void lg(String str) {
  lgs.print(str);
}
void lg(int s) {
  lgs.print(s);
}
void lg(float s) {
  lgs.print(s);
}
void lg(long s) {
  lgs.print(s);
}
void lgln(String str) {
  lg(str);
  lgs.println("");
}
void lgchar(char s) {
  lgs.print(s);
}
//===================================================================
