//===================================================================
#define  lgs  Serial
static const long sBaud = 115200;
//-------------------------------------------------------------------
String lgName = "Temp", lgVersion = "1.0";
boolean lgKey = false; char lgStart = '{'; char lgEndss = '}';
String lgBack = ""; bool lgBfKey = false;
//===================================================================
void lg_setup(String s, String v, boolean _lgkey, char a, char b) {
  lgs.begin(sBaud); while (!lgs);;
  lgName = s; lgVersion = v;
  lgStart = a; lgEndss = b; lgKey = _lgkey;
  lg(F(">>==================================<<")); lg();
  lg(F("Soft.Name     = ")); lgln(lgName);
  lg(F("Soft.Version  = ")); lgln(lgVersion);
  lg(F("Logs.BaudRate = ")); lg(sBaud); lg();
  lg(F("Logs.Buf.Show = ")); lg(lgKey ? "True" : "False"); lg();
  lg(F("Logs.Buf.Start= ")); lg(lgStart); lg();
  lg(F("Logs.Buf.Endss= ")); lg(lgEndss); lg();
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
void lg_loop() {
  while ( lgs.available() ) {
    char c = lgs.read();
    if (lgKey) lgs.write(c);
    lg_save(c);
  }
}
//===================================================================
void lg_clear() {
  lgBack = "";
}
void lg_show() {
  lg(lgBack);
}
void lg_save(char c) {
  if (c == lgStart ) {
    lgBfKey = true; lg_clear();
  }
  if (lgBfKey) lgBack += c;
  if (c == lgEndss ) {
    lgBfKey = false; 
    //if(lg_work(lgBack)) 
    lllss(lgBack);
    lg_clear();
  }
}
//===================================================================
/*
void lg_work() {
  //return;
  if (lgBack.length() <= 0) { //lg("E");
  } else if (lgBack.indexOf("AllData") > 0) {
    lg_clear();
    
  } else if (lgBack.indexOf("bbb") > 0) {
    lg("b"); lg_clear();
  } else if (lgBack.indexOf("ccc") > 0) {
    lg("c"); lg_clear();
  }
}
*/
//===================================================================
