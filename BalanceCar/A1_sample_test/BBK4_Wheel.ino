//===================================================================
//===================================================================
typedef struct Wheel {
  //----------------------------------------------------------
  double R;//cm/Radius;//int CircumFerence;
  int I;//Interrupt;中断端口号，不是Pin号
  double N;//20*2;码盘的槽数的2倍
  unsigned int intN;//中断计数器
  Motor M;//定义电动机
  int Cs = 0; //StartKey = 0;//轮子刚启动的PWM值
  double sMax, sNow;//, sNow2; //km/h;//最大速度，当前速度
  double Rcx = 0;//速度换算中间值
  //----------------------------------------------------------
  unsigned long t = micros(); //中断计时
  unsigned long tx = 0;//
  //----------------------------------------------------------
  void init(double r, double n, int i, Motor m) {
    R = r; M = m; I = i; N = 2 * n;
    //Rcx =3600*1000(((2*3.1415926*R/N)*intT)/loopms)/1000/100;
    //Rcx =3600*1000*2*3.1415926*R/N*intT/loopms/1000/100;
    //Rcx =3600*1000/1000/100*2*3.1415926*R/N*intT/loopms;
    //Rcx =3600*1000/1000/100*2*3.1415926;//*R/N*intT/loopms;
    Rcx = 226.19 * R / N;//km/h
    Rcx = 226190 * R / N;//m/h
    //attachInterrupt(I, Interrupt_run, FALLING);
  }
  void init(double r, double n, int i, int ma, int mb, int me) {
    R = r; I = i; N = 2 * n; M.init(ma, mb, me);
    Rcx = 226.19 * R / N;
    //attachInterrupt(I, interrupt_run, FALLING);
  }
  //  void interrupt_run() {
  //    intN++;
  //  }
  //  void int_clear() {//interrupt_clear
  //    intN = 0;
  //  }
  void sets(int ms, int n, String s) {
    //---------------------------------------------------------
    Cs = 0; speedCalc();
    for (int i = 0; i < 255; i++) {
      runs(i); smartDelay(ms); speedCalc();
      if (sNow > 0 && Cs == 0) {
        Cs = i; break;
      }
    }
    //---------------------------------------------------------
    sMax = 0; speedCalc();
    for (int i = 0; i < n; i++) {
      runs(255); smartDelay(ms); speedCalc();
      if (sMax < sNow) sMax = sNow;
    }
    //---------------------------------------------------------
    runs(0); smartDelay(ms * 6); speedCalc();
    //---------------------------------------------------------
    lg(s); lg(" ");
    lg("Cs="); lg(Cs); lg(" ");
    lg("sMax="); lg(sMax); lg();
    //----------------------------------------------------------
  }
  void runs(int v) {
    M.runs(v);
  }
  void runx(double v) {
    runx((int)v);
  }
  void runx(int v) {
    if (v > 10)
      v = map(v, 0, 255, Cs, 200);
    runs(v);
  }
  void speedTimes() {
    //------------------------------------------
    //1秒=1000毫秒=1000000微秒//millisecond毫秒/微秒microseconds
    tx = micros() - t; t = micros(); //millis();
    //------------------------------------------
  }
  void speedCalc() {
    //------------------------------------------
    // lg("tx=");lg(tx);lg();
    if (tx == 0)sNow = 99999; else sNow = Rcx / tx;
    //------------------------------------------
  }
} Wheel;
//===================================================================
