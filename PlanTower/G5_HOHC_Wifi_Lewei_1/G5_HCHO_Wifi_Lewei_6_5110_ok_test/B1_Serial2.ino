//===================================================================
#define S2 Serial2
long S2_Baud = 9600;
boolean S2logKey = false;
//===================================================================
void S2_init(String ss_name, long btl, boolean lgKey) {
  S2logKey = lgKey; S2_Baud = btl;
  S2.begin(S2_Baud); delay(200);
  lg(ss_name); lg(F(".start = ")); lg(S2_Baud); lg();
}
//===================================================================
void S2_feed() {
  while (S2.available()) {
    byte c = S2.read();
    if (S2logKey) lg(c);
    //HCHOCheck(c);
  }
}
//===================================================================
