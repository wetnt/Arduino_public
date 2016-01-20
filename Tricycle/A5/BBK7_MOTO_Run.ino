//===================================================================
int RightV, LeftsV;
PID rPID, lPID;
//===================================================================
void Moto_Run_Init() { //运行速度初始化
  //---------------------------------------------------------
  MotoRunAB( 10000, 10000); smartDelay(3000);
  MotoRunAB(-10000, -10000); smartDelay(3000);
  MotoRunAB(0, 0); smartDelay(1000);
  //---------------------------------------------------------
  PIDInit ( &rPID ); PIDInit ( &lPID );
  rPID.Proportion = 0.5;  lPID.Proportion = 0.5;
  rPID.Integral = 0.5;    lPID.Integral = 0.5;
  rPID.Derivative = 0.0;  lPID.Derivative = 0.0;
  //---------------------------------------------------------
}
//===================================================================
void Moto_Run_loop() { //10ms运行一次
  rPID.SetPoint = 100.0;
  lPID.SetPoint = 100.0;
  int rOut, lOut;
  rOut = PIDCalc ( &rPID, speed_right_min );
  lOut = PIDCalc ( &lPID, speed_lefts_min );
  MotoRunAB(rOut, lOut); 
  //int speed_min = Math.max(speed_right_min, speed_lefts_min);
  //smartDelay(speed_min);
}
//===================================================================
