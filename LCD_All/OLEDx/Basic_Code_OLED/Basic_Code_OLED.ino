static const String codeName = "Battery_Test_b!";
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  //------------------------------------------------
  oled_Init();
  MPU6050_setup();
  //------------------------------------------------
}
void loop() {
 MPU6050_read();
 smartDelay(100);
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); oled_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
