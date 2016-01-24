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
  //-----------------------------
  BKMOTOR_Init(22, 24, 26, 28, 30, 32);
  Interrupt_setIn();//车轮码盘中断
  //-----------------------------
  Car_Init();
  Car_Speed_Start_R();
  //-----------------------------
}
void loop() {
  //---------------------------------
  //Car_Run_loop();
  //---------------------------------
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    //APC220_Feed();
    //------------------------------------------
  } while (millis() - start < ms);
}

