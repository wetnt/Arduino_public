//===================================================================
#include <PID_v1.h>
//===================================================================
double rSetpoint, rInput, rOutput;
double lSetpoint, lInput, lOutput;
double Kp = 0, Ki = 0, Kd = 0;//251
PID rPID(&rSetpoint, &rOutput, &rSetpoint, Kp, Ki, Kd, DIRECT);
PID lPID(&lSetpoint, &lOutput, &lSetpoint, Kp, Ki, Kd, DIRECT);
//===================================================================
void Moto_Run_Init() { //运行速度初始化
  //---------------------------------------------------------
  MotoRunAB( 10000, 10000); smartDelay(3000);
  MotoRunAB(-10000, -10000); smartDelay(3000);
  MotoRunAB(0, 0); smartDelay(1000);
  //---------------------------------------------------------
  //rPID.SetMode(AUTOMATIC);  lPID.SetMode(AUTOMATIC);
  //---------------------------------------------------------
}
//===================================================================
void Moto_Run_loop() { //10ms运行一次
  //---------------------------------------------------------
  rSetpoint = 200;  lSetpoint = 200;
  //---------------------------------------------------------
  rPID.SetTunings(Kp, Ki, Kd);
  lPID.SetTunings(Kp, Ki, Kd);
  //---------------------------------------------------------
  rInput = speed_right_min;  lInput = speed_lefts_min;
  rPID.Compute();  lPID.Compute();
  //---------------------------------------------------------
  MotoRunAB(rOutput, lOutput);
  //---------------------------------------------------------
}
//===================================================================
