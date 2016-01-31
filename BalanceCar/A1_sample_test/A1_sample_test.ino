/*
1.Tricycle三轮小车
2.MEGA2560
3.Serial  是log输出
4.Serial3 是RC遥控命令输入输出
5.
*/

float cm = 0;

void setup() {
  //-----------------------------
  log_setup();
  delay(500);
  //-----------------------------
  Car_Init();
  //-----------------------------
}
void loop() {
  //---------------------------------
  //Car_loop();//自带50ms延时
  //car_info_log();
  //---------------------------------
  //rc_cmd_loop();
  //smartDelay(10);
  //---------------------------------
  Car_IntN_Test_loop();
  //---------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();
    //------------------------------------------
  } while (millis() - start < ms);
}

