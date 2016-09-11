/*
  //--------------------------------------------
  1.履带小车
  2.Nano328
  3.Serial  是log输出
  4.Serial3 是RC遥控命令输入输出
  5.
  //--------------------------------------------
*/
void setup() {
  //--------------------------------------------
  lgsetup("BBK Tank 2 !");
  //-----------------------------
  rc_setup();
  delay(500);
  //-----------------------------
}
void loop() {
  //car_info_log();
  Car_stop();
  smartDelay(100);
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    lgFeed(); rcFeed();
  } while (millis() - start < ms);
}

