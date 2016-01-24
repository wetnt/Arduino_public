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
double SpeedMaxR = 0, SpeedMaxL = 0;
int CarStartR = 0, CarStartL = 0;
//int CarCtMaxR = 0, CarCtMaxL = 0;
int loopms = 10;//50ms
//===================================================================
void Car_Init() { //PID初始化
  //---------------------------------------------------------
  rPID.SetMode(AUTOMATIC);  lPID.SetMode(AUTOMATIC);
  //---------------------------------------------------------
  lg("Car_Run_Init()"); lg();
  //---------------------------------------------------------
}
void Car_Speed_Start() { //运行速度初始化
  //---------------------------------------------------------
  lg("Car_Speed_Start():"); lg(loopms); lg("ms ");
  //---------------------------------------------------------
  CarStartR = 0;
  for (int i = 0; i < 256; i++) {
    Interrupt_clear(); MotorRunAB(i, 0); smartDelay(loopms);
    rSpeed = 22.5 * intR / loopms; Interrupt_clear();
    if (rSpeed > 0 && CarStartR == 0) {
      CarStartR = i; break;
    }
  }
  lg("CarStartR="); lg(CarStartR); lg();
  //---------------------------------------------------------
  // Interrupt_clear(); MotorRunAB(0, 0); smartDelay(1000);
  //---------------------------------------------------------
  lg("Car_Speed_Max():"); lg(loopms); lg("ms ");
  //---------------------------------------------------------
  for (int i = 0; i < 30; i++) {
    Interrupt_clear(); MotorRunAB(255, 0); smartDelay(loopms);
    rSpeed = 22.5 * intR / loopms; Interrupt_clear();
    if (SpeedMaxR < rSpeed) SpeedMaxR = rSpeed;
  }
  lg("SpeedMaxR="); lg(SpeedMaxR); lg();
  //---------------------------------------------------------
  Interrupt_clear(); MotorRunAB(0, 0);
  //---------------------------------------------------------
}
//===================================================================

void Car_loop() { //10ms运行一次
  //---------------------------------------------------------
  rSetpoint = 1.0;  lSetpoint = 1.0;
  //---------------------------------------------------------
  //rPID.SetTunings(Kp, Ki, Kd);
  //lPID.SetTunings(Kp, Ki, Kd);
  //---------------------------------------------------------
  rSpeed = 22.5 * intR / loopms;
  lSpeed = 22.5 * intL / loopms;
  Interrupt_clear();
  rPID.Compute();  lPID.Compute();
  //---------------------------------------------------------
  MotorRunAB(rOutput, 0);
  Car_Run_Show();
  //---------------------------------------------------------
  smartDelay(loopms);
  //---------------------------------------------------------
}
void Car_Run_Show() {
  //---------------------------------------------------------
  //lg("speed_right_min=");  lg(speed_right_min);  lg();
  //lg("speed_lefts_min=");  lg(speed_lefts_min);  lg();
  //---------------------------------------------------------
  //lg("intR="); lg(intR); lg(" ");  //Interrupt_clear();
  //---------------------------------------------------------
  lg("rSetpoint=");
  lg(rSetpoint); lg(" ");
  lg("rSpeed=");
  lg(rSpeed); lg(" ");
  lg("rOutput=");
  lg(rOutput); lg();
  //---------------------------------------------------------
}
//===================================================================
