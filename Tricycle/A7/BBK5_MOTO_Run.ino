//===================================================================
#include <PID_v1.h>
//===================================================================
double rSetpoint, rInput, rOutput;
double lSetpoint, lInput, lOutput;
double Kp = 1, Ki = 0, Kd = 0;//251
PID rPID(&rSetpoint, &rOutput, &rSetpoint, Kp, Ki, Kd, DIRECT);
PID lPID(&lSetpoint, &lOutput, &lSetpoint, Kp, Ki, Kd, DIRECT);
//===================================================================
int speed_right = 0, speed_lefts = 0;
//===================================================================
void Moto_Run_Init() { //运行速度初始化
  //---------------------------------------------------------
  MotoRunAB( 1000,  1000); smartDelay(1000);
  MotoRunAB(-1000, -1000); smartDelay(1000);
  MotoRunAB(0, 0); smartDelay(1000);
  //---------------------------------------------------------
  //rPID.SetMode(AUTOMATIC);  lPID.SetMode(AUTOMATIC);
  //---------------------------------------------------------
}
//===================================================================
void Moto_Run_loop() { //10ms运行一次
  //---------------------------------------------------------
  rSetpoint = 1.0;  lSetpoint = 1.0;
  //---------------------------------------------------------
  rPID.SetTunings(Kp, Ki, Kd);
  lPID.SetTunings(Kp, Ki, Kd);
  //---------------------------------------------------------
  rInput = spdr;  lInput = spdl;
  rPID.Compute();  lPID.Compute();
  //---------------------------------------------------------
  MotoRunAB(rOutput, lOutput);
  Moto_Run_Show();
  //---------------------------------------------------------
}
void Moto_Run_Show() {
  //---------------------------------------------------------
  //lg("speed_right_min=");  lg(speed_right_min);  lg();
  //lg("speed_lefts_min=");  lg(speed_lefts_min);  lg();
  //---------------------------------------------------------
  lg("rInput="); lg(rInput); lg(" ");  lg("rOutput="); lg(rOutput); lg();
  lg("spdr="); lg(spdr); lg(" ");  lg("spdl="); lg(spdl); lg();
  //---------------------------------------------------------
}
//===================================================================
