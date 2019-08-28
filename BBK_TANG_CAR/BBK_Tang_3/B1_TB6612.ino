//===================================================================
//TB6612
//===================================================================
typedef struct BBK_TB6612 {
  //----------------------------------------------------------
  int PWMA = 0; int AIN1 = 0; int AIN2 = 0;
  int PWMB = 0; int BIN1 = 0; int BIN2 = 0;
  //----------------------------------------------------------
  void setup(int pa, int a1, int a2, int b1, int b2, int pb) {
    PWMA = pa; AIN1 = a1; AIN2 = a2;
    PWMB = pb; BIN1 = b1; BIN2 = b2;
    pinMode(pa, OUTPUT); pinMode(a1, OUTPUT); pinMode(a2, OUTPUT);
    pinMode(pb, OUTPUT); pinMode(b1, OUTPUT); pinMode(b2, OUTPUT);
  }
  void ma(int f, int v) {
    moto_run(AIN1, AIN2, PWMA, f, v);
  }
  void mb(int f, int v) {
    moto_run(BIN1, BIN2, PWMB, f, v);
  }
  void moto_run(int a, int b, int p, int f, int v) {
    if (f == 0)         {
      digitalWrite(a, LOW); digitalWrite(b, LOW );
    } else if (f == 1)  {
      digitalWrite(a, LOW); digitalWrite(b, HIGH);
    } else if (f == -1) {
      digitalWrite(a, HIGH); digitalWrite(b, LOW );
    }
    analogWrite(p, v);
  }
} BBK_TB6612;
//===================================================================
