static const String codeName = "JTWX_Test_2!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  LCD_128x64_setup();
  WS8X8_setup();
  //DHT_setup();
  MPU6050_setup();
  DHT_setup();
  Solar_Setup();
  tLoop_Setup();
  //------------------------------------------------
}
void loop() {
  if (ts_loop(1)) {
    DHT_loop();
    //DHT_show();
    LCD_128x64_loop();
    Solar_loop();
    //Solar_log();
    logshow();
  }
  //for(int i=0;i<100;i++){
  //WS8X8_loop();
  //}
  //B_analogRead_loop();
  //B_analogRead_log();
  //B_analogRead_Lcd();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); WS8X8_loop(); MPU6050_read();
    //------------------------------------------
  } while (millis() - start < ms);
}
static void smartDelay2(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();
    //------------------------------------------
  } while (millis() - start < ms);
}
