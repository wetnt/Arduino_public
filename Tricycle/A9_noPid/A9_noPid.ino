/*
1.Tricycle三轮小车
2.MEGA2560
3.Serial  是log输出
4.Serial1 是RC遥控命令输入输出
5.
*/

float cm = 0;

void setup() {
  //-----------------------------
  log_setup();
  rc_setup();
  //-----------------------------
  Car_Init();
  //Car_Speed_Start();
  //-----------------------------
}
void loop() {
  //---------------------------------
  rc_cmd_loop();
  //---------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    //APC220_Feed();
    lgFeed();
    rcFeed();
    //------------------------------------------
  } while (millis() - start < ms);
}

