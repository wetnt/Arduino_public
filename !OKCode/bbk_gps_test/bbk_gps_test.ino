static const String codeName = "bbk_gps_test!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  //ss_init(String name, int rx, int tx, long btl, boolean lgKey);
  ss_init(F("GPS,170MHz"), 11, 10, 9600, false);
  //------------------------------------------------
}
void loop() {
  ss_feed();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}

