//===================================================================
int CarR = 0, CarL = 0;
//===================================================================
Wheel wr, wl;
int loopMS = 50;//50ms
double carSpeedMax = 0;
//===================================================================
void Car_Init() { //小车初始化
  //---------------------------------------------------------
  lg(F("Car_Init()..."));
  wr.init(2.5, 20, 0, 8, 9, 10);
  wl.init(2.5, 20, 1, 11, 12, 13);
  attachInterrupt(wr.I, interrupt_run_r, FALLING);
  attachInterrupt(wl.I, interrupt_run_l, FALLING);
  delay(500);
  lg(F("ok")); lg();
  //---------------------------------------------------------
}
void interrupt_run_r() {
  wr.intN++;
  wr.speedTimes();
};
void interrupt_run_l() {
  wl.intN++;
  wl.speedTimes();
};
void Car_Speed_Start() { //运行速度初始化
  lg(F("Car_Speed_Start()...")); lg();
  wl.sets(20, 20, "wl");
  wr.sets(20, 20, "wr");
  carSpeedMax = min(wl.sMax, wr.sMax);
  lg(F("Car_Speed_Start()...ok CarSpeedMax = ")); lg(carSpeedMax); lg();
}
void Car_IntN_Test_loop() {
  lg("rIntN="); lg(wr.intN); lg(" = "); lg(wr.sNow); lg("\t");
  lg("lIntN="); lg(wl.intN); lg(" = "); lg(wl.sNow); lg("\t");
  lg();
  smartDelay(1000);
}
void Car_SetVt(int r, int l) {
  CarR = r; CarL = l;
}
void Car_loop() {
  wr.runx(CarR); wl.runx(CarL); smartDelay(loopMS);
}
void Car_loopx(int r, int l, int delayMS) { //10ms运行一次
  //---------------------------------------------------------
  loopMS = delayMS;
  wr.runx(r); wl.runx(l); smartDelay(loopMS);
  //---------------------------------------------------------
  //lg("CarCt = "); lg(r); lg(","); lg(l); lg(" ");
  //lg("Speed = "); lg(wr.sNow); lg(" "); lg(wr.sNow2); lg(" = "); lg(wl.sNow); lg(" "); lg(wl.sNow2); lg(" ");
  //lg();
  //---------------------------------------------------------
}
//===================================================================
