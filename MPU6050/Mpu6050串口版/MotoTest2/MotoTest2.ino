
#include "Timer.h"
Timer t;
int rl,rr;

void setup() {
  //------------------------------------------------------------
  Serial.begin(115200);
  //------------------------------------------------------------
  achou_init();
  Step_Init();
    attachInterrupt(0, Step_Right, CHANGE);
  attachInterrupt(1, Step_Lefts, CHANGE);
  //------------------------------------------------------------
  int tickEvent = t.every(2000, mt);
  int tickEvent2 = t.every(200, Step_Show);
  //------------------------------------------------------------
  Serial.println("Motor Go!");
  //------------------------------------------------------------
}

void loop() {
  //------------------------------------------------------------
  t.update();
  SetMotor(rl, rr);
  //------------------------------------------------------------
  //------------------------------------------------------------
  //------------------------------------------------------------
}

void mt(){
  rl=rl+50;
  rr=rr+50;
  if(rl>250)rl=0;
  if(rr>250)rr=0;

  Serial.print("rlr= ");
  Serial.print(rl);
  Serial.print(" - ");
  Serial.print(rr);
  Serial.println("");
  
}

///////////////////////////////interrupt for Speed/////////////////////////////////
long Step_t = micros();//计时器
long Step_v_l, Step_v_r;
int Step_count_leftt = 0, Step_count_right = 0;
//------------------------------------------------------------
void Step_Show() {
  Step_Loop();
  //------------------------------------------------------------
  Serial.print(Step_v_l);
  Serial.print("-");
  Serial.print(Step_v_r);
  Serial.println("");  
  //------------------------------------------------------------
  Serial.print(Step_count_leftt);
  Serial.print("-");
  Serial.print(Step_count_right);
  Serial.println("");
  //------------------------------------------------------------
}
//------------------------------------------------------------
void Step_Init() {
  attachInterrupt(0, Step_Right, CHANGE);
  attachInterrupt(1, Step_Lefts, CHANGE);
}
void Step_Right() {
  // 编码器码盘计数加一
  Step_count_right += 1;
}
void Step_Lefts() {
  // 编码器码盘计数加一
  Step_count_leftt += 1;
}
//------------------------------------------------------------
void Step_Loop() {
  //------------------------------------------------------------
  long t = micros() - Step_t;
  Step_t = micros();
  Step_v_l = Step_count_leftt * 1000 / t;
  Step_v_r = Step_count_right * 1000 / t;
  Step_count_leftt = 0;
  Step_count_right = 0;
  //------------------------------------------------------------
}
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
