//==============================================================================
int motorA1, motorA2, motorAS;
int motorB1, motorB2, motorBS;
//==============================================================================
void BKMOTOR_Init(int aa, int ac, int as, int ba, int bc, int bs) {
  //----------------------------------------------------------
  motorA1 = aa;  motorA2 = ac;  motorAS = as;
  motorB1 = ba;  motorB2 = bc;  motorBS = bs;
  pinMode(motorA1, OUTPUT);  pinMode(motoAr2, OUTPUT);  pinMode(motorAS, OUTPUT);
  pinMode(motorB1, OUTPUT);  pinMode(motoBr2, OUTPUT);  pinMode(motorBS, OUTPUT);
  //----------------------------------------------------------
  char MotorPin[30];
  sprintf(MotorPin, "MotoPin:%02d,%02d,%02d,%02d,%02d,%02d\0", aa, ac, as, ba, bc, bs);
  lg(MotorPin); lg();
  //----------------------------------------------------------
}
void MotorRunAB(int va, int vb) {
  MotorRun(va, motorA1, motorA2, motorAS);
  MotorRun(vb, motorB1, motorB2, motorBS);
}
//==============================================================================
void MotorRun(int v, int m1, int m2, int ms) {
  //----------------------------------------------------------
  if (1 == 0) {
  }  else if (v == 0) {
    digitalWrite(m1, LOW);    digitalWrite(m2, LOW);
  }  else if (v > 0)  {
    digitalWrite(m1, LOW);    digitalWrite(m2, HIGH);
  }  else if (v < 0)  {
    digitalWrite(m1, HIGH);   digitalWrite(m2, LOW);
  }
  //----------------------------------------------------------
  int s = abs(v); if (s > 255) s = 255; 
  analogWrite(ms, s);
  //----------------------------------------------------------
}
//==============================================================================

