//===================================================================
int CarR = 0, CarL = 0;
//===================================================================
Wheel wr, wl;
double carSpeedMax = 1.0;
//===================================================================
//JGA25-371全金属电机、超耐磨65MM橡胶轮胎、3MM铝合金车身
//电机带有高精度码盘,一圈有334个脉冲
//※左边两根黄线是电机两极
//※绿线和白线是脉冲输出线，理论用一根即可，两根同时用可测出电机转向
//※红线和黑线是编码器电源接线，红正黑负，电压3.3V-5V
//===================================================================
double Radius = 6.5 / 2; //65mm
double WheelN = 334 * 34; //=11356;
//double WheelN = 334 / 2 * 103; //=17201;
//===================================================================
void Car_Init() { //小车初始化
  //---------------------------------------------------------
  //LOW 当引脚为低电平时，触发中断
  //CHANGE 当引脚电平发生改变时，触发中断
  //RISING 当引脚由低电平变为高电平时，触发中断
  //FALLING 当引脚由高电平变为低电平时，触发中断.
  //---------------------------------------------------------
  lg(F("Car_Init()..."));
  wr.init(Radius, WheelN, 0, 9, 10, 8); //轮子半径,槽数（一圈）,中断,A,B,EN
  wl.init(Radius, WheelN, 1, 11, 12, 13);
  attachInterrupt(wr.I, interrupt_run_r, FALLING);//LOW/CHANGE/RISING/FALLING
  attachInterrupt(wl.I, interrupt_run_l, FALLING);
  delay(500);
  lg(F("ok")); lg();
  //---------------------------------------------------------
}
void interrupt_run_r() {
  wr.intN++;
};
void interrupt_run_l() {
  wl.intN++;
};
void Car_Speed_Start(int ms, int N) { //运行速度初始化
  lg(F("Car_Speed_Start()...")); lg();
  wl.sets(ms, N, "wl");
  wr.sets(ms, N, "wr");
  carSpeedMax = min(wl.sMax, wr.sMax);
  lg(F("CarSpeedMax = ")); lg(carSpeedMax); lg();
}
void Car_SetVt(int r, int l) {
  CarR = r; CarL = l;
}
void Car_loop() {
  wr.runx(CarR); wr.speedCalc(loopMS); wl.runx(CarL); wl.speedCalc(loopMS);
}
//===================================================================
