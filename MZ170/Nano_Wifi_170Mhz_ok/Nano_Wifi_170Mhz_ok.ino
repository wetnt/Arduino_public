//===================================================================
static const String codeName = "Nano_WiFi_170MHz!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  Beep_Setup();
  //------------------------------------------------
  ss_init(F("170MHz"), 12, 13, 9600, true);
  //ss_init(F("WiFi,170MHz"), 11, 10, 9600, false);
  //------------------------------------------------
}
void loop() {
  lgFeed(); ss_feed();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}

