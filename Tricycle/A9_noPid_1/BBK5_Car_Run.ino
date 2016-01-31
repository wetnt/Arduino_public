//===================================================================
Wheel wr, wl;
int loopms = 10;//50ms
//===================================================================
void Car_Init() { //小车初始化
  //---------------------------------------------------------
  lg(F("Car_Init()..."));
  wr.init(2.5, 0, 20, 8, 9, 10);
  wl.init(2.5, 1, 20, 11, 12, 13);
  attachInterrupt(wr.I, interrupt_run_r, FALLING);
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
void Car_Speed_Start() { //运行速度初始化
  lg(F("Car_Speed_Start()...")); lg();
  wl.sets(100, 2, "wl");
  wr.sets(100, 2, "wr");
  lg(F("Car_Speed_Start()...ok")); lg();
}
void Car_loop(int r, int l) { //10ms运行一次
  //---------------------------------------------------------
  //r = map(r, 0, 255, -255, 255);
  //l = map(l, 0, 255, -255, 255);
  //---------------------------------------------------------
  wr.runx(r);    wl.runx(l);
  smartDelay(loopms);
  wr.speedNow(loopms); wl.speedNow(loopms);
  //---------------------------------------------------------
  lg("CarCt = ");lg(r);lg(",");lg(l);lg(" ");
  lg("Speed = ");lg(wr.sNow);lg(" ");lg(wl.sNow);lg();
  //---------------------------------------------------------
}
//===================================================================
