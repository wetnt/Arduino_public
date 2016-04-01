static const String codeName = "G5_HOHC_Wifi_Lewei_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  wifi_Init(true,true,true);
  NetLinkTest_BBKGPS();
  //------------------------------------------------  
  Work_Loop_Run();
  //------------------------------------------------
}
void loop() {
  lgFeed();
  Work_Loop();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();
    //------------------------------------------
  } while (millis() - start < ms);
}
//=====================================================
