//===================================================================
#include <PID_v1.h>
//===================================================================
double rSetpoint, rSpeed, rOutput;
double lSetpoint, lSpeed, lOutput;
//double Kp = 0.9, Ki = 0.12, Kd = 0;//251
double Kp = 85, Ki = 12, Kd = 0; //251
PID rPID(&rSpeed, &rOutput, &rSetpoint, Kp, Ki, Kd, DIRECT);
PID lPID(&lSpeed, &lOutput, &lSetpoint, Kp, Ki, Kd, DIRECT);
//PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
//---------------------------------------------------------
void PID_Init() { //PID初始化
  //---------------------------------------------------------
  lg(F("PID_Init()..."));
  rSetpoint = 0.8;  lSetpoint = 0.8;
  rPID.SetMode(AUTOMATIC);  lPID.SetMode(AUTOMATIC);
  lg("ok"); lg();
  //---------------------------------------------------------
}
//===================================================================
void Car_Kpi(double p, double i, double d) {
  Kp = p; Ki = i; Kd = d;
  lg(Kp); lg("="); lg(Ki); lg("="); lg(Kd); lg();
}
void Car_loop(int N) { //10ms运行一次
  //---------------------------------------------------------
  lg(F("Car_loop()...")); lg();
  smartDelay(3000);
  wr.speedNow(loopms);
  //---------------------------------------------------------
  for (int i = 0; i < N; i++) {
    //---------------------------------------------------------
    //rPID.SetTunings(Kp, Ki, Kd);
    //lPID.SetTunings(Kp, Ki, Kd);
    //---------------------------------------------------------
    wr.speedNow(loopms); rSpeed = wr.sNow;
    rPID.Compute(); wr.runx(rOutput);
    //---------------------------------------------------------
    Car_Run_Show();
    //---------------------------------------------------------
    smartDelay(loopms);
    //---------------------------------------------------------
  }
  //---------------------------------------------------------
  wr.runs(0);
  //---------------------------------------------------------
}
void Car_Run_Show() {
  //---------------------------------------------------------
  lg(rSetpoint);
  lg(","); lg(rSpeed);
  lg(","); lg(rOutput);
  lg();
  //---------------------------------------------------------
}
//===================================================================
