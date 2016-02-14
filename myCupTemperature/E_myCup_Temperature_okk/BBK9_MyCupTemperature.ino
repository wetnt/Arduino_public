typedef struct CupTemperature {
  int myTemperature = 100;
  boolean bCheckDown = false;
  boolean bCheckUpup = false;
  void init(int k) {
    myTemperature = k;
    bCheckDown = false;
    bCheckUpup = false;
  }
  boolean checkDown(float t) {
    if (t > myTemperature) bCheckDown = true;
    if (bCheckDown && t < myTemperature) {
      bCheckDown = false; return true;
    } else {
      return false;
    }
  }
  boolean checkUpup(float t) {
    if (t < myTemperature) bCheckUpup = true;
    if (bCheckUpup && t > myTemperature) {
      bCheckUpup = false; return true;
    } else {
      return false;
    }
  }
} CupTemperature;
//=======================================================================
CupTemperature ca, cb, cc;
void myCup_Init(int a, int b, int c) {
  ca.init(a); cb.init(b); cc.init(c);
}
void myCupCheck() {
  float mt = GetMyCupTemperature();
  lg("myCupTemperature="); lg(mt); lg();
  //--------------------------------------------
  if (ca.checkDown(mt)) Beep(8);
  if (cb.checkDown(mt)) Beep(10);
  if (cc.checkDown(mt)) Beep(12);
  //--------------------------------------------
  if (ca.checkUpup(mt)) Beep(3);
  if (cb.checkUpup(mt)) Beep(2);
  if (cc.checkUpup(mt)) Beep(1);
  //--------------------------------------------
}
//=======================================================================
