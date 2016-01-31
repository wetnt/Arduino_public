//==============================================================================
void digitalAB(int a, int av, int b, int bv) {
  digitalWrite(a, av); digitalWrite(b, bv);
}
//==============================================================================
typedef struct Motor {
  int A, B, E;
  void init(int a, int b, int e) {
    A = a; B = b; E = e;
    pinMode(A, OUTPUT); pinMode(B, OUTPUT); pinMode(E, OUTPUT);
  }
  void runs(int v) {
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
