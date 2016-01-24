//===================================================================
int loopms = 10;//50ms
//===================================================================
typedef struct Wheel {
  //----------------------------------------------------------
  int R;//cm/Radius;//int CircumFerence;
  int I;//Interrupt;中断端口号，不是Pin号
  int N;//20;码盘的槽数
  static  unsigned int intT;//中断计数器
  Motor M;
  int Cs = 0; //StartKey = 0;
  double sMax, sNow;//km/h;
  double Rcx = 0;
  //----------------------------------------------------------
  void Init(int r, Motor m, int i, int n) {
    R = r; M = m; I = i; N = n;
    //Rcx =3600*1000(((2*3.1415926*R/N)*intT)/loopms)/1000/100;
    //Rcx =3600*1000*2*3.1415926*R/N*intT/loopms/1000/100;
    //Rcx =3600*1000/1000/100*2*3.1415926*R/N*intT/loopms;
    //Rcx =3600*1000/1000/100*2*3.1415926;//*R/N*intT/loopms;
    Rcx = 226.19 * R / N;
    attachInterrupt(I, Interrupt_run, FALLING);
  }
  static void Interrupt_run() {
    intT++;
  }
  void Interrupt_clear() {
    intT = 0;
  }
  void Set() {
    //---------------------------------------------------------
    Cs = 0;
    for (int i = 0; i < 256; i++) {
      //-----------------------------
      Interrupt_clear();
      Run(i); smartDelay(loopms);
      sNow = Rcx * intR / loopms;
      Interrupt_clear();
      //-----------------------------
      if (sNow > 0 && Cs == 0) {
        Cs = i; break;
      }
      //-----------------------------
    }
    //---------------------------------------------------------
    for (int i = 0; i < 30; i++) {
      //-----------------------------
      Interrupt_clear();
      Run(i); smartDelay(loopms);
      sNow = Rcx * intR / loopms;
      Interrupt_clear();
      //-----------------------------
      if (sMax < sNow) sMax = sNow;
      //-----------------------------
    }
    //---------------------------------------------------------
    Interrupt_clear(); Run(0);
    //---------------------------------------------------------
    lg("sMax="); lg(sMax); lg();
    //----------------------------------------------------------
  }
  void Run(int v) {
    M.Run(v);
  }
} Wheel;
//===================================================================
Wheel Wr,Wl;
//===================================================================
//===================================================================
