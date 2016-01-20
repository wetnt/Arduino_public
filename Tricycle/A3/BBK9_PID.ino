typedef struct PID
{
  int  SetPoint;              //设定目标 Desired Value
  long SumError;              //误差累计
  double  Proportion;         //比例常数 Proportional Cons
  double  Integral;           //积分常数 Integral Const
  double  Derivative;         //微分常数 Derivative Const
  int LastError;              //Error[-1]
  int PrevError;              //Error[-2]
} PID;

/*******************************************************************************
* 函数名称 : IncPIDCalc
* 函数描述 : 增量式 PID 控制计算
* 函数输入 : int 当前位置
* 函数输出 : 无
* 函数返回 : 增量式PID结果
*******************************************************************************/
int IncPIDCalc(int NextPoint)
{
  int iError, iIncpid;
  //当前误差
  iError = sptr->SetPoint - NextPoint;
  //增量计算
  iIncpid = sptr->Proportion * iError               //E[k]项
            - sptr->Integral   * sptr->LastError    //E[k－1]项
            + sptr->Derivative * sptr->PrevError;   //E[k－2]项
  //存储误差，用于下次计算
  sptr->PrevError = sptr->LastError;
  sptr->LastError = iError;
  //返回增量值
  return (iIncpid);
}
/*******************************************************************************
* 函数名称 : LocPIDCalc
* 函数描述 : 位置式 PID 控制计算
* 函数输入 : int 当前位置
* 函数输出 : 无
* 函数返回 : 位置式PID结果
*******************************************************************************/
int LocPIDCalc(int NextPoint)
{
  int  iError, dError;
  iError = sptr->SetPoint - NextPoint;        //偏差
  sptr->SumError += iError;                   //积分
  dError = iError - sptr->LastError;          //微分
  sptr->LastError = iError;
  return (sptr->Proportion * iError           //比例项
          + sptr->Integral * sptr->SumError   //积分项
          + sptr->Derivative * dError);       //微分项
}
