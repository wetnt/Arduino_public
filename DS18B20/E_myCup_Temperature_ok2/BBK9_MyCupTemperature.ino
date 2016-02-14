typedef struct CupTemperature {
  int myTemperature = 100;
  boolean TemperatureCk = false;
  void init(int k) {
    myTemperature = k;
    TemperatureCk = false;
  }
  boolean check(float t) {
    if (t > myTemperature) TemperatureCk = true;
    if (TemperatureCk && t < myTemperature) {
      TemperatureCk = false;
      return true;
    } else {
      return false;
    }
  }
} CupTemperature;
//=======================================================================
CupTemperature ca, cb, cc;
void myCup_Init(int a,int b,int c) {
  ca.init(a); cb.init(b); cc.init(c);
}
void myCupCheck() {
  float mt = GetMyCupTemperature();
  lg("myCupTemperature="); lg(mt); lg();
  if (ca.check(mt)) Beep(10);
  if (cb.check(mt)) Beep(8);
  if (cc.check(mt)) Beep(5);
}
//=======================================================================
