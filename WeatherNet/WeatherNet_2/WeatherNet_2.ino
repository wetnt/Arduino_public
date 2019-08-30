void setup() {
  lgsetup(F("TangBox 8x8 LED Matrix Test!Net Line"));
  RGB8X8_setup(); RGB8X8_text("OK");  
  wifi_Init();
}
void loop() {
  loopfalsh();
  RGB8X8_loop(); 
  WeatherHttpGet(); 
  WeatherHttpExp(); 
  smartDelay(5000);
}
//===============================================
void loopfalsh() {
  //------------------------------------------
  lgFeed();
  //------------------------------------------
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    loopfalsh();
  } while (millis() - start < ms);
}
//===============================================
