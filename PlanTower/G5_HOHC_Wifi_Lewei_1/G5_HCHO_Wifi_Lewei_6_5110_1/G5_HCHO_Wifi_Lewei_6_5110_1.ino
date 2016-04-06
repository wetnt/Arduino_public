static const String codeName = "G5_HOHC_Wifi_Lewei_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  LCD5110_setup();
  //------------------------------------------------
  Si7021_setup();
  //------------------------------------------------
  S1_init(F("G5"), 9600, false);
  //S2_init(F("WIFI"), 9600, true);
  S3_init(F("HCHO"), 9600, false);
  //------------------------------------------------
  wifi_Init(true, false, false); NetLinkTest_BBKGPS();
  //------------------------------------------------
  //Work_Loop_Run();
  //------------------------------------------------
}
void loop() {
  lgFeed(); S1_feed(); S2_feed(); S3_feed();
  Si7021_loop(); HCHO_loop();
  Work_Loop(); Work_Loop_Run_A();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();
    S1_feed(); S2_feed(); S3_feed();
    Si7021_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//=====================================================
