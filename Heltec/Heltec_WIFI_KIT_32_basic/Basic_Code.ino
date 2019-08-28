static const String codeName = "Battery_Test_b!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  LCD1602_setup(); LCD1602_Clear();
  LCD1602_Show(0, 0, codeName);
  //------------------------------------------------
  B_analogRead_Setup();
  //------------------------------------------------
  oled_Init();
  MPU6050_setup();
  //------------------------------------------------
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
