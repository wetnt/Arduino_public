//===================================================================
static const String codeName = "Nano_WiFi_170MHz!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  //ss_init(String name, int rx, int tx, long btl, boolean lgKey);
  ss_init(F("WiFi,170MHz"), 11, 10, 9600, false);
  DS18B20_Init();
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

