int motoA1, motoA2, motoAS;
int motoB1, motoB2, motoBS;
//==============================================================================
void BKMOTO_Init(int aa, int ac, int as, int ba, int bc, int bs) {
  motoA1 = aa;  motoA2 = ac;  motoAS = as;
  motoB1 = ba;  motoB2 = bc;  motoBS = bs;
  pinMode(motoA1, OUTPUT);  pinMode(motoA2, OUTPUT);  pinMode(motoAS, OUTPUT);
  pinMode(motoB1, OUTPUT);  pinMode(motoB2, OUTPUT);  pinMode(motoBS, OUTPUT);
}
void MotoRunAB(int va, int vb) {
  MotoRun(va, motoA1, motoA2, motoAS);
  MotoRun(vb, motoB1, motoB2, motoBS);
}
//==============================================================================
void MotoRun(int v, int m1, int m2, int ms) {
  //-------------------------------------------------
  int f = v > 0 ? 1 : -1;
  int s = Math.abs(v);
  //-------------------------------------------------
  if (1 == 0) {
  }  else if (f == 0) {
    digitalWrite(m1, LOW);    digitalWrite(m2, LOW);
  }  else if (f > 0)  {
    digitalWrite(m1, LOW);    digitalWrite(m2, HIGH);
  }  else if (f < 0)  {
    digitalWrite(m1, HIGH);   digitalWrite(m2, LOW);
  }
  //-------------------------------------------------
  if (s > 1024) s = 1024; analogWrite(ms, s);
  //-------------------------------------------------
}
//==============================================================================

