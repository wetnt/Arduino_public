//===================================================================
static const String codeName = "bbk_gps_test!";
void setup() {
  //-------------------------------------
  Pin_setup();//必须首先执行，防止烧毁硬件
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  //ss_init(String name, int rx, int tx, long btl, boolean lgKey);
  ss_init(F("GPS,170MHz"), 11, 10, 9600, false);
  //------------------------------------------------
  Dog_Start();
  //------------------------------------------------
}
void loop() {
  lgFeed(); ss_feed(); Dog_Loop();zLastCheck();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed(); Dog_Loop();
    //------------------------------------------
  } while (millis() - start < ms);
}

