/*
  //--------------------------------------------
  1.唐麦克纳姆轮小车
  2.Nano328
  3.Serial  是log输出
  4.Serial3 是RC遥控命令输入输出
  //--------------------------------------------
  //https://www.arduino.cn/thread-23162-1-1.html
  //https://zhuanlan.zhihu.com/p/20282234
*/
void setup() {
  lgsetup("BBK_Tang_8_runtest");
  oled_setup();delay(1000);
  rc_setup();
  moto_setup();
}
void loop() {
  //Car_stop();
  Car_runfull();
  oled_loop();
  smartDelay(1000);
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    lgFeed(); rcFeed();
  } while (millis() - start < ms);
}

