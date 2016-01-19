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
  Serial1.begin(9600);
  //-----------------------------
  IR_Setup(53, 51, 49);
  BKMOTO_Init(22, 24, 26, 28, 30, 32);
  Interrupt_setIn();//车轮码盘中断
  //-----------------------------
  lg("$JML,CAR,SAN,0,0,0,0,0,0;");
  //-----------------------------
}
void loop() {
  //---------------------------------
  IR_Loop();  IR_Show(false);
  //---------------------------------
  //cm = PingGetCM();
  cm = IR_Get();
  lg(cm);
  //---------------------------------
}
