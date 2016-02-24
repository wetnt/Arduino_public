static const String codeName = "Battery_Test_b!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  B_analogRead_Setup();
  //------------------------------------------------
}
void loop() {
  B_analogRead_loop();
  B_analogRead_log();
  B_analogRead_Lcd();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();
    //------------------------------------------
  } while (millis() - start < ms);
}
