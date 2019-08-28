/*
  //--------------------------------------------
  1.唐麦克纳姆轮小车
  2.Nano328
  3.Serial  是log输出
  4.Serial3 是RC遥控命令输入输出
  //--------------------------------------------
*/
void setup() {
  lgsetup("唐麦克纳姆轮小车");
  oled_setup(); 
  delay(1000);
  rc_setup();
  moto_setup();
}
void loop() {
  oled_loop();
  Car_stop();
  smartDelay(800);
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    lgFeed(); rcFeed();
  } while (millis() - start < ms);
}

