//===================================================================
//===================================================================
typedef struct Wheel {
  //----------------------------------------------------------
  //double PI;//
  double R;//cm/Radius;//int CircumFerence;
  int I;//Interrupt;中断端口号，不是Pin号
  double N;//码盘一圈脉冲数
  unsigned int intN;//中断计数器
  Motor M;//定义电动机
  int Cs = 0; //StartKey = 0;//轮子刚启动的PWM值
  double sMax, sNow;//, sNow2; //km/h;//最大速度，当前速度
  double Rcx = 0;//速度换算中间值
  //----------------------------------------------------------
  void init(double r, double n, int i, int ma, int mb, int me) {
    //---------------------------------------------------------
    //v=距离/时间=(2*PI*R/N)/(tx/1000000微秒)=(R/N)*2*PI*1000000/tx==cm/秒;
    //v=距离/时间=(R/N)*2*PI*1000000/tx * 3600/(1000*100) ==km/h;
    //v=(R/N/tx) * (2*PI*1000000) * (3600/(1000*100)) ==km/h;
    //v=(R/N/tx) * (2*PI) * (3600*1000000/(100000)) ==km/h;
    //v=(R/N/tx) * (2*PI) * (3600*10) ==km/h;
    //v=(R/N/tx) * (2*PI*36000) ==km/h;
    //v=(R/N/tx) * (226194.6672) ==km/h;
    //v=(226195*R/N)/tx ==km/h;
    //---------------------------------------------------------
    R = r; I = i; N = n; M.init(ma, mb, me);
    //---------------------------------------------------------
    Rcx = 226195 * R / N;//km/h
    //Rcx = 226195 * 1000 * R / N; //m/h
    //---------------------------------------------------------
    //attachInterrupt(I, interrupt_run, FALLING);
    //---------------------------------------------------------
  }
  void sets(int ms, int n, String s) {
    //---------------------------------------------------------
    Cs = 0; speedCalc(ms);
    for (int i = 0; i < 255; i++) {
      runs(i); smartDelay(ms); speedCalc(ms);
      if (sNow > 0 && Cs == 0) {
        Cs = i; break;
      }
    }
    //---------------------------------------------------------
    sMax = 0; speedCalc(ms);
    for (int i = 0; i < n; i++) {
      runs(255); smartDelay(ms); speedCalc(ms);
      //lg("sNow="); lg(sNow); lg();
      if (sMax < sNow) sMax = sNow;
    }
    runs(0); smartDelay(ms * 6); speedCalc(ms);
    //---------------------------------------------------------
    if (0) {
      sMax = 0; speedCalc(ms);
      for (int i = 0; i < n; i++) {
        runs(-255); smartDelay(ms); speedCalc(ms);
        //lg("sNow="); lg(sNow); lg();
        if (sMax < sNow) sMax = sNow;
      }
      runs(0); smartDelay(ms * 6); speedCalc(ms);
    }
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
    if (abs(v) < 10)  v = 0;
    else if (v >  10) v = map(v, 0,  255,  Cs,  255);
    else if (v < -10) v = map(v, 0, -255, -Cs, -255);
    runs(v);
  }
  void speedCalc(int ms) {
    sNow = (double)intN * Rcx / ms / 1000;
    intN = 0;
  }
} Wheel;
//===================================================================
