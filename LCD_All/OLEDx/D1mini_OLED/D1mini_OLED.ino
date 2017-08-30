static const String codeName = "PlanTowerG5_x_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  oled_setup();
  //------------------------------------------------
}
void loop() {
  //ss_feed();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    //lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}
