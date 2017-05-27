typedef struct Solar_Read {
  int vPin = A0;
  int delayMs = 20;
  float vx, vSum;
  int v[10];
  void init(int pin, int delayKey) {
    vPin = pin; delayMs = delayKey;
    vx = 0; vSum = 0;
  }
  void Solar_loop() {
    vSum = 0.0f;
    for (int i = 0; i < 10; i++) {
      v[i] = analogRead(vPin);
      vSum += v[i];
      smartDelay(delayMs);
    }
    vSum /= 10.0f;
  }
} Solar_Read;
Solar_Read a1, a2, a3, a4;
void B_analogRead_Setup() {
  a1.init(A4, 10);
  a2.init(A5, 10);
  a3.init(A6, 10);
}
void B_analogRead_loop() {
  a1.loopRun();
  //b2.loopRun();
  // b3.loopRun();
}
void B_analogRead_log() {
  lg(a1.vSum); lg(','); lg(a2.vSum); lg(','); lg(a3.vSum); lg(','); lg();
}
void B_analogRead_Lcd() {
  String s = "";
  s.concat(a1.vx);  s.concat(' ');
  s.concat(a2.vx);  s.concat(' ');
  s.concat(a3.vx);  s.concat(' ');
  //LCD1602_Show(0, 0, s);
}

