//===================================================================
#define S3 Serial3
long S3_Baud = 9600;
boolean S3logKey = false;
//===================================================================
void S3_init(String ss_name, long btl, boolean lgKey) {
  S3logKey = lgKey; S3_Baud = btl;
  S3.begin(S3_Baud); delay(200);
  lg(ss_name); lg(F(".start = ")); lg(S3_Baud); lg();
}
//===================================================================
void S3_feed() {
  while (S3.available()) {
    byte c = S3.read();
    if (S3logKey) lg(c);
    HCHOCheck(c);
  }
}
//===================================================================
