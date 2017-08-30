static const String codeName = "PlanTowerG5_x_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  ss_init(F("G5"), 10, 11, 9600, false); //String name, int rx, int tx, long btl, boolean lgKey
  //------------------------------------------------
  ws8x8_setup();
  tLoop_Setup();
}
void loop() {
  ss_feed();
  if (ts_loop(100)) {
    ws8x8_txt_loop();
  }
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}
