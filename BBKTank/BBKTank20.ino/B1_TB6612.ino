//TB6612
//------------------------------------------
//VM  接12V以内电源
//VCC 接5V电源
//GND 接电源负极
//A1A2,B1B2,接电机
//------------------------------------------
char CmdMoto[40];
//------------------------------------------
//PWMA 接单片机PWM口
//真值表AIN1,AIN2,BIN1,BIN2,正反转
int PWMA = 9;
int AIN1 = 8;
int AIN2 = 7;
int STBY = 6;
int BIN1 = 5;
int BIN2 = 4;
int PWMB = 3;
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
  sprintf(CmdMoto,"moto: $%02d,%02d,%02d,%02d*\0",rv, rf, lv, lf);
  rcSend(CmdMoto, true);
  lg(CmdMoto); lg();  
  moto_lefts(rv, rf);moto_right(lv, lf);
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

