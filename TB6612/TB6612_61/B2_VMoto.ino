//TB6612

int f_PWMA = 6;
int f_AIN1 = A1;
int f_AIN2 = A0;
int f_BIN1 = 4;
int f_BIN2 = 2;
int f_PWMB = 3;

int b_PWMA = 5;
int b_AIN1 = 7;
int b_AIN2 = 8;
int b_BIN1 = 13;
int b_BIN2 = 12;
int b_PWMB = 11;

BBK_TB6612 ta, tb;
void moto_setup() {
  ta.setup(f_PWMA, f_AIN1, f_AIN2, f_BIN1, f_BIN2, f_PWMB);
  tb.setup(b_PWMA, b_AIN1, b_AIN2, b_BIN1, b_BIN2, b_PWMB);
}
void moto_work() {
  ta.ma(1, 0); ta.mb(1, 0);
  tb.ma(1, 0); tb.mb(1, 0);
 // delay(5000);

  for (int i = 0; i < 255; i++) {
    ta.ma(1, i); ta.mb(1, i);
    tb.ma(1, i); tb.mb(1, i);
    Serial.println(i);
    delay(50);
  }
  ta.ma(1, 0); ta.mb(1, 0);
  tb.ma(1, 0); tb.mb(1, 0);
  //delay(5000);
  for (int i = 0; i < 255; i++) {
    ta.ma(-1, i); ta.mb(-1, i);
    tb.ma(-1, i); tb.mb(-1, i);
    Serial.println(i);
    delay(50);
  }
  //delay(5000);
  ta.ma(1, 0); ta.mb(1, 0);
  tb.ma(1, 0); tb.mb(1, 0);
  //delay(5000);
}

