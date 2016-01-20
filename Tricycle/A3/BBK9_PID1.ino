typedef struct PID {
  double Command; //输入指令
  double Proportion;  //比例系数
  double Integral;   //积分系数
  double Derivative;  //微分系数
  double pre2Err;  //前两拍误差
  double preErr;  //前一拍误差
} PID;
double PIDCale(PID *p, double feedback)
{
  double Err, pErr, dErr, dU;
  Err = p->Command - feedback; //当前误差
  pErr = Err - p->preErr; //比例项增量式误差
  dErr = Err - 2 * p->preErr + p->pre2Err; //微分项增量式误差
  dU = p->Proportion * pErr + p->Derivative * dErr + p->Integral * Err; //控制量增量
  p->pre2Err = p->preErr;
  p->preErr = Err;
  return dU;
}
void PIDInit(PID *p)
{
  memset(p, 0, sizeof(PID)); //初始化
}
