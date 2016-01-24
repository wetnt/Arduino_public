//===================================================================
//===================================================================
typedef struct Wheel {
  //----------------------------------------------------------
  double R;//cm/Radius;//int CircumFerence;
  int I;//Interrupt;中断端口号，不是Pin号
  int N;//20*2;码盘的槽数的2倍
  unsigned int intN;//中断计数器
  Motor M;
  int Cs = 0; //StartKey = 0;
  double sMax, sNow;//km/h;
  double Rcx = 0;
  //----------------------------------------------------------
  void init(double r, int i, int n, int ma, int mb, int me) {
    R = r; I = i; N = 2 * n; M.init(ma, mb, me);
    Rcx = 226.19 * R / N;
    //attachInterrupt(I, interrupt_run, FALLING);
  }
  void init(double r, int i, int n, Motor m) {
    R = r; M = m; I = i; N = 2 * n;
    //Rcx =3600*1000(((2*3.1415926*R/N)*intT)/loopms)/1000/100;
    //Rcx =3600*1000*2*3.1415926*R/N*intT/loopms/1000/100;
    //Rcx =3600*1000/1000/100*2*3.1415926*R/N*intT/loopms;
    //Rcx =3600*1000/1000/100*2*3.1415926;//*R/N*intT/loopms;
    Rcx = 226.19 * R / N;
    //attachInterrupt(I, Interrupt_run, FALLING);
  }
  //  void interrupt_run() {
  //    intN++;
  //  }
  void int_clear() {//interrupt_clear
    intN = 0;
  }
  void sets(int ms, int n, String s) {
    //---------------------------------------------------------
    Cs = 0;
    for (int i = 0; i < 256; i++) {
      runs(i); smartDelay(ms); speedNow(ms);
      if (sNow > 0 && Cs == 0) {
        Cs = i - 10; break;
      }
    }
    //---------------------------------------------------------
    sMax = 0;
    for (int i = 0; i < n; i++) {
      runs(255); smartDelay(ms); speedNow(ms);
      if (sMax < sNow) sMax = sNow;
    }
    //---------------------------------------------------------
    runs(0);
    //---------------------------------------------------------
    lg(s); lg(" ");
    lg("Cs="); lg(Cs); lg(" ");
    lg("sMax="); lg(sMax); lg();
    //----------------------------------------------------------
  }
  void runs(int v) {
    int_clear(); M.runs(v);
  }
  void runx(int v) {
    v = map(v, 0, 255, Cs, 255);
    runs(v);
  }
  void speedNow(int ms) {
    sNow = Rcx * intN / ms;
    //lg(intN); lg();
    int_clear();
  }
} Wheel;
//===================================================================
