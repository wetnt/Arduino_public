//TB6612
char CmdMoto[40];
//------------------------------------------
int PWMA = 13;
int AIN1 = 11;
int AIN2 = 12;
int STBY = 41;
int BIN1 = 36;
int BIN2 = 37;
int PWMB = 10;
//------------------------------------------
int pinLed = 13;
void moto_setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}
//------------------------------------------
void moto_stop() {
  digitalWrite(STBY, LOW);
}
void moto_run(int rv, int rf, int lv, int lf) {
  moto_lefts(rv, rf); moto_right(lv, lf);
  sprintf(CmdMoto, "moto: $%02d,%02d,%02d,%02d*\0", rv, rf, lv, lf);
  rcSend(CmdMoto, true); lg(CmdMoto); lg();
}
void moto_lefts(int v, int f) {
  if (f == 0) {
    digitalWrite(STBY, LOW);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW );
  } else if (f == -1) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH );
  } else if (f == 1) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW );
  }
  analogWrite(PWMA, v);
}
void moto_right(int v, int f) {
  if (f == 0) {
    digitalWrite(STBY, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW );
  } else if (f == 1) {
    digitalWrite(STBY, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH );
  } else if (f == -1) {
    digitalWrite(STBY, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW );
  }
  analogWrite(PWMB, v);
}
//------------------------------------------

