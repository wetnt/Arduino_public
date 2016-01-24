int motoA1, motoA2, motoAS;
int motoB1, motoB2, motoBS;
//==============================================================================
void BKMOTOR_Init(int aa, int ac, int as, int ba, int bc, int bs) {
  //-------------------------------------------------
  motoA1 = aa;  motoA2 = ac;  motoAS = as;
  motoB1 = ba;  motoB2 = bc;  motoBS = bs;
  pinMode(motoA1, OUTPUT);  pinMode(motoA2, OUTPUT);  pinMode(motoAS, OUTPUT);
  pinMode(motoB1, OUTPUT);  pinMode(motoB2, OUTPUT);  pinMode(motoBS, OUTPUT);
  //-------------------------------------------------
  char MotorPin[30];
  sprintf(MotorPin, "MotoPin:%02d,%02d,%02d,%02d,%02d,%02d\0", aa, ac, as, ba, bc, bs);
  lg(MotorPin); lg();
}
void MotorRunAB(int va, int vb) {
  MotorRun(va, motoA1, motoA2, motoAS);
  MotorRun(vb, motoB1, motoB2, motoBS);
}
//==============================================================================
void MotorRun(int v, int m1, int m2, int ms) {
  //-------------------------------------------------
  int f = v > 0 ? 1 : -1;
  int s = abs(v);
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
  if (s > 255) s = 255; analogWrite(ms, s);
  //-------------------------------------------------
}
//==============================================================================

