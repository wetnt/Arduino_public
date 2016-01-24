//==============================================================================
void digitalAB(int a, int av, int b, int bv) {
  digitalWrite(a, av); digitalWrite(b, bv);
}
//==============================================================================
typedef struct Motor {
  int A;
  int B;
  int E;
  void Init(int a, int b, int e) {
    A = a; B = b; E = e;
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(E, OUTPUT);
  }
  void Run(int v) {
    //----------------------------------------------------------
    if (1 == 0) {}
    else if (v == 0) digitalAB(A, LOW, B, LOW);
    else if (v > 0)  digitalAB(A, LOW, B, HIGH);
    else if (v < 0)  digitalAB(A, HIGH, B, LOW);
    //----------------------------------------------------------
    int s = abs(v); if (s > 255) s = 255;
    analogWrite(E, s);
    //----------------------------------------------------------
  }
} Motor;
//==============================================================================
Motor MotorA, MotorB;
//==============================================================================
void BKMOTOR_Init(int aa, int ac, int as, int ba, int bc, int bs) {
  //----------------------------------------------------------
  MotorA.Init(aa, ac, as);
  MotorB.Init(ba, bc, bs);
  //----------------------------------------------------------
  char MotorPin[30];
  sprintf(MotorPin, "MotoPin:%02d,%02d,%02d,%02d,%02d,%02d\0", aa, ac, as, ba, bc, bs);
  lg(MotorPin); lg();
  //----------------------------------------------------------
}
void MotorRunAB(int va, int vb) {
  MotorA.Run(va);
  MotorB.Run(vb);
}
//==============================================================================

