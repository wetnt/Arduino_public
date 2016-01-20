/*====================================================================================================
//PID
=====================================================================================================*/
typedef struct PID {
  double SetPoint; // 设定目标Desired value
  double Proportion; // 比例常数Proportional Const
  double Integral; // 积分常数Integral Const
  double Derivative; // 微分常数Derivative Const
  double LastError; // Error[-1]
  double PrevError; // Error[-2]
  double SumError; // Sums of Errors
} PID;
/*====================================================================================================
PID计算函数
=====================================================================================================*/
double PIDCalc( PID *pp, double NextPoint ) {
  double dError, Error;
  Error = pp->SetPoint - NextPoint; // 偏差
  pp->SumError += Error; // 积分
  dError = pp->LastError - pp->PrevError; // 当前微分
  pp->PrevError = pp->LastError;
  pp->LastError = Error;
  return (pp->Proportion * Error // 比例项
          + pp->Integral * pp->SumError // 积分项
          + pp->Derivative * dError // 微分项
         );
}
/*====================================================================================================
PID结构体变量初始化函数
=====================================================================================================*/
void PIDInit (PID *pp) {
  memset ( pp, 0, sizeof(PID));
}
/*====================================================================================================
读取输入变量函数（在此设定为固定值100）
======================================================================================================*/
double sensor (void) {
  return 100.0;
}
/*====================================================================================================
输出变量控制函数
======================================================================================================*/
void actuator(double rDelta) {
}

//主函数
/*
void main_test(void) {
  PID sPID; // PID Control Structure
  double rOut; // PID Response (Output)
  double rIn; // PID Feedback (Input)

  PIDInit ( &sPID ); // Initialize Structure
  sPID.Proportion = 0.5; // Set PID Coefficients
  sPID.Integral = 0.5;
  sPID.Derivative = 0.0;
  sPID.SetPoint = 100.0; // Set PID Setpoint

  for (;;) {// Mock Up of PID Processing
    rIn = sensor (); // Read Input
    rOut = PIDCalc ( &sPID, rIn ); // Perform PID Interation
    actuator ( rOut ); // Effect Needed Changes
  }

}
*/
