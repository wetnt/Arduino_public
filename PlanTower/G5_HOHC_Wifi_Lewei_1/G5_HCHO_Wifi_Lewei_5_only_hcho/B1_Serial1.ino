//===================================================================
#define S1 Serial1
long S1_Baud = 9600;
boolean S1logKey = false;
//===================================================================
void S1_init(String ss_name, long btl, boolean lgKey) {
  S1logKey = lgKey; S1_Baud = btl;
  S1.begin(S1_Baud); delay(200);
  lg(ss_name); lg(F(".start = ")); lg(S1_Baud); lg();
}
//===================================================================
void S1_feed() {
  while (S1.available()) {
    byte c = S1.read();
    if (S1logKey) lg(c);
   //G5Feed(c);
  }
}
//===================================================================
