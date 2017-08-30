static const String codeName = "PlanTowerG5_x_1!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  ss_init(F("G5"), D1,D2, 9600, true); //String name, int rx, int tx, long btl, boolean lgKey
  //------------------------------------------------
}
void loop() {
  ss_feed();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}
