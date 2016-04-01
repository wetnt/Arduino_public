static const String codeName = "G5_HOHC_Wifi_Lewei_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  S1_init(F("G5"), 9600, true);
  S2_init(F("HCHO"), 9600, true);
  //------------------------------------------------
}
void loop() {
  S1_feed();
  S2_feed();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); S1_feed(); S2_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}
