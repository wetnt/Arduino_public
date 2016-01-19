int motoA1, motoA2, motoAS;
int motoB1, motoB2, motoBS;
//==============================================================================
void BKMOTO_Init(int aa, int ac, int as, int ba, int bc, int bs) {
  motoA1 = aa;  motoA2 = ac;  motoAS = as;
  motoB1 = ba;  motoB2 = bc;  motoBS = bs;
  pinMode(motoA1, OUTPUT);  pinMode(motoA2, OUTPUT);  pinMode(motoAS, OUTPUT);
  pinMode(motoB1, OUTPUT);  pinMode(motoB2, OUTPUT);  pinMode(motoBS, OUTPUT);
}
void MotoRunA(int a, int s) {
  MotoRun(a, s, motoA1, motoA2, motoAS);
}
void MotoRunB(int a, int s) {
  MotoRun(a, s, motoB1, motoB2, motoBS);
}
//==============================================================================
void MotoRun(int a, int s, int m1, int m2, int ms) {
  //-------------------------------------------------
  if (a == 0) {
    digitalWrite(m1, LOW);  digitalWrite(m2, LOW);
  } else if (a > 0) {
    digitalWrite(m1, LOW);  digitalWrite(m2, HIGH);
  } else if (a < 0) {
    digitalWrite(m1, HIGH); digitalWrite(m2, LOW);
  }
  //-------------------------------------------------
  if (s < 0) s = 0;
  if (s > 1024) s = 1024;
  analogWrite(ms, s);
  //-------------------------------------------------
}
//==============================================================================

