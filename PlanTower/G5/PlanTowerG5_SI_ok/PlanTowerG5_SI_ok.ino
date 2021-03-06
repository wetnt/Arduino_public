static const String codeName = "PlanTowerG5_x_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  oled_Init();
  Si7021_setup();
  //------------------------------------------------
  ss_init(F("G5"), 10, 11, 9600, false);//String name, int rx, int tx, long btl, boolean lgKey
  //------------------------------------------------
}
void loop() {
  Si7021_loop();
  ss_feed();
  oled_loop();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}
