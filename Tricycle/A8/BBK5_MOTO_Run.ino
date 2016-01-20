//===================================================================
#include <PID_v1.h>
//===================================================================
double rSetpoint, rSpeed, rOutput;
double lSetpoint, lSpeed, lOutput;
double Kp = 200, Ki = 5, Kd = 0;//251
PID rPID(&rSpeed, &rOutput, &rSetpoint, Kp, Ki, Kd, DIRECT);
PID lPID(&lSpeed, &lOutput, &lSetpoint, Kp, Ki, Kd, DIRECT);
//PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
//===================================================================
void Moto_Run_Init() { //运行速度初始化
  //---------------------------------------------------------
  //MotoRunAB( 1000,  0); smartDelay(1000);
  //MotoRunAB(-1000, -1000); smartDelay(1000);
  //MotoRunAB(0, 0); smartDelay(1000);
  //---------------------------------------------------------
  rPID.SetMode(AUTOMATIC);  lPID.SetMode(AUTOMATIC);
  //---------------------------------------------------------
}
//===================================================================
void Moto_Run_loop() { //10ms运行一次
  //---------------------------------------------------------
  rSetpoint = 1.0;  lSetpoint = 1.0;
  //---------------------------------------------------------
  //rPID.SetTunings(Kp, Ki, Kd);
  //lPID.SetTunings(Kp, Ki, Kd);
  //---------------------------------------------------------
  rSpeed = 22.5 * intR / 50;
  lSpeed = 22.5 * intL / 50;
  //Interrupt_clear();
  rPID.Compute();  lPID.Compute();
  //---------------------------------------------------------
  MotoRunAB(rOutput, 0);
  Moto_Run_Show();
  //---------------------------------------------------------
}
void Moto_Run_Show() {
  //---------------------------------------------------------
  //lg("speed_right_min=");  lg(speed_right_min);  lg();
  //lg("speed_lefts_min=");  lg(speed_lefts_min);  lg();
  //---------------------------------------------------------
  //lg("intR="); lg(intR); lg(" ");  
  lg("rSpeed="); lg(rSpeed); lg(" ");  
  lg("rOutput="); lg(rOutput); lg();
  Interrupt_clear();
  //---------------------------------------------------------
}
//===================================================================
