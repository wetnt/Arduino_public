//===================================================================
#include <PID_v1.h>
//===================================================================
int PidCtR, PidCtL;//PID控制目标(原始)
//---------------------------------------------------------
double rSetpoint, rSpeed, rOutput;
double lSetpoint, lSpeed, lOutput;
//---------------------------------------------------------
double Kp = 200, Ki = 214, Kd = 1.7; //
//$FF7F7F7F00FF,1350,0900,0000*
//---------------------------------------------------------
PID rPID(&rSpeed, &rOutput, &rSetpoint, Kp, Ki, Kd, DIRECT);
PID lPID(&lSpeed, &lOutput, &lSetpoint, Kp, Ki, Kd, DIRECT);
//---------------------------------------------------------
void PID_Init() { //PID初始化
  //---------------------------------------------------------
  lg(F("PID_Init()..."));
  rPID.SetMode(AUTOMATIC);  lPID.SetMode(AUTOMATIC);
  lg(Kp); lg(","); lg(Ki); lg(","); lg(Kd); lg("...");
  lg("ok"); lg();
  //---------------------------------------------------------
}
//===================================================================
void PID_Set(double p, double i, double d) {
  //---------------------------------------------------------
  lg("PID_Set="); lg(Kp); lg("="); lg(Ki); lg("="); lg(Kd); lg();
  //---------------------------------------------------------
  Kp = p; Ki = i; Kd = d;
  rPID.SetTunings(Kp, Ki, Kd);
  lPID.SetTunings(Kp, Ki, Kd);
  //---------------------------------------------------------
}
//===================================================================
void Pid_Loop() {
  //---------------------------------------------------------
  int fr = PidCtR >= 0 ? 1 : -1;
  int fl = PidCtL >= 0 ? 1 : -1;
  //---------------------------------------------------------
  //PID控制目标(直接值)
  rSetpoint = abs(PidCtR) * carSpeedMax / 255;
  lSetpoint = abs(PidCtL) * carSpeedMax / 255;
  //---------------------------------------------------------
  rSpeed = wr.sNow; rPID.Compute();
  lSpeed = wl.sNow; lPID.Compute();
  //---------------------------------------------------------
  Car_SetVt(rOutput * fr, lOutput * fl);
  //---------------------------------------------------------
}
//===================================================================
void PID_Test(double V, int N) { //V目标速度,N运行次数
  //---------------------------------------------------------
  PID_Value_Show(); delay(500);
  //---------------------------------------------------------
  int ms = 50; wr.speedCalc(ms); //50ms控制周期
  //---------------------------------------------------------
  rPID = PID(&rSpeed, &rOutput, &rSetpoint, Kp, Ki, Kd, DIRECT);
  rPID.SetMode(AUTOMATIC);
  rSetpoint = V;//rPID.SetTunings(Kp, Ki, Kd);
  //---------------------------------------------------------
  for (int i = 0; i < N; i++) {
    //---------------------------------------------------------
    wr.speedCalc(ms); rSpeed = wr.sNow;
    rPID.Compute(); wr.runx(rOutput); delay(ms);
    PID_Test_Out();
    //---------------------------------------------------------
  }
  //---------------------------------------------------------
  wr.runs(0); PID_Value_Show();
  //---------------------------------------------------------
}
void PID_Test_Out() {
  //---------------------------------------------------------
  for (int i = 0; i < 5; i++) {
    lg(rSetpoint);
    lg(","); lg(rSpeed);
    lg(","); lg(rOutput);
    lg();
  }
  //---------------------------------------------------------
}
void PID_Value_Show() {
  lg(F("PID_Value_Show()..."));
  lg(F(" PID=")); lg(Kp); lg("="); lg(Ki); lg("="); lg(Kd);
  lg(F(" vPoint=")); lg(rSetpoint); lg();
}
//===================================================================
/*
2．PID调试一般原则
a.在输出不振荡时，增大比例增益P。
b.在输出不振荡时，减小积分时间常数Ti。
c.在输出不振荡时，增大微分时间常数Td。
3．一般步骤
a.确定比例增益P
确定比例增益P 时，首先去掉PID的积分项和微分项，一般是令Ti=0、Td=0（具体见PID的参数设定说明），使PID为纯比例调节。
输入设定为系统允许的最大值的60%~70%，由0逐渐加大比例增益P，直至系统出现振荡；再反过来，从此时的比例增益P逐渐减小，直至系统振荡消失，记录此时的比例增益P，
设定PID的比例增益P为当前值的60%~70%。比例增益P调试完成。
b.确定积分时间常数Ti
比例增益P确定后，设定一个较大的积分时间常数Ti的初值，然后逐渐减小Ti，直至系统出现振荡，之后在反过来，逐渐加大Ti，直至系统振荡消失。
记录此时的Ti，设定PID的积分时间常数Ti为当前值的150%~180%。积分时间常数Ti调试完成。
c.确定积分时间常数Td
积分时间常数Td一般不用设定，为0即可。若要设定，与确定 P和Ti的方法相同，取不振荡时的30%。
d.系统空载、带载联调，再对PID参数进行微调，直至满足要求
http://www.geek-workshop.com/thread-704-1-1.html 我的自平衡小车D4——PID控制器——第一次的直立行走
http://www.geek-workshop.com/thread-23-1-1.html
*/
