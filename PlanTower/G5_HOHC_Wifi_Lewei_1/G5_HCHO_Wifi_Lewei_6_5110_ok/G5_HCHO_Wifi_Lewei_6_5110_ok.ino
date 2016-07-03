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
  wifi_Init(false, false, false); NetLinkTest_BBKGPS();
  //------------------------------------------------
  tLoop_Setup();
  //------------------------------------------------
  HCHO_Ask(); Si7021_read();
  LCD_Show_All(); LG_Show_All();//Lewei_Loop();
  //------------------------------------------------
  Dog_Start();
  //------------------------------------------------
}
void loop() {
  lgFeed(); S1_feed(); S2_feed(); S3_feed();
  Work_Loop(); Dog_Loop();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); S1_feed(); S2_feed(); S3_feed();Dog_Loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//=====================================================
