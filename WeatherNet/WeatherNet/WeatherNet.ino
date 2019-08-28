void setup() {
  lgsetup(F("TangBox 8x8 LED Matrix Test!Net Line"));
  wifi_Init();
}
void loop() {
  loopfalsh();
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    loopfalsh();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
void loopfalsh() {
  lgFeed();
}
//===============================================
