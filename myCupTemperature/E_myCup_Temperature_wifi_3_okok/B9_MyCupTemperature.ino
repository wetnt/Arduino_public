typedef struct CupTemperature {
  int myTemperature = 100;
  boolean bCheckDown = false;
  boolean bCheckUpup = false;
  void init(int k) {
    myTemperature = k;
    bCheckDown = false;
    bCheckUpup = false;
  }
  boolean checkDown(float t) {//下降沿
    if (t > myTemperature) bCheckDown = true;
    if (bCheckDown && t < myTemperature) {
      bCheckDown = false; return true;
    } else {
      return false;
    }
  }
  boolean checkUpup(float t) {//上升沿
    if (t < myTemperature) bCheckUpup = true;
    if (bCheckUpup && t > myTemperature) {
      bCheckUpup = false; return true;
    } else {
      return false;
    }
  }
} CupTemperature;
//=======================================================================
CupTemperature ca, cb, cc, cd;
void myCup_Init(int a, int b, int c, int d) {
  ca.init(a); cb.init(b); cc.init(c); cd.init(d);
}
void myCupCheck() {
  float mt = GetMyCupTemperature();
  lg(F("myCupTemperature = ")); lg(mt); lg();
  //--------------------------------------------
  if (ca.checkDown(mt)) Beep(8);
  if (cb.checkDown(mt)) Beep(10);
  if (cc.checkDown(mt)) Beep(12);
  if (cd.checkDown(mt)) Beep(18);
  //--------------------------------------------
  if (ca.checkUpup(mt)) Beep(1);
  if (cb.checkUpup(mt)) Beep(1);
  if (cc.checkUpup(mt)) Beep(1);
  if (cd.checkUpup(mt)) Beep(1);
  //--------------------------------------------
}
//=======================================================================
