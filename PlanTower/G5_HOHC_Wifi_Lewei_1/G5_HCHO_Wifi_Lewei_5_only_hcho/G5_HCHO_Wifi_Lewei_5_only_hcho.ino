static const String codeName = "G5_HOHC_Wifi_Lewei_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  S1_init(F("G5"), 9600, false);
  S2_init(F("WIFI"), 9600, true);
  S3_init(F("HCHO"), 9600, false);
  //------------------------------------------------
}
void loop() {
  AskHCHO();
  smartDelay(2000);
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); //S1_feed(); S2_feed(); 
    S3_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}
