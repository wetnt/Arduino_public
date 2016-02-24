#define  BatteryKey 0.00282f
typedef struct Battery {
  int vPin = A0;
  int delayMs = 20;
  float vx, vSum, vd = BatteryKey;
  int v[10];
  void init(int pin, int delayKey, float vdx = BatteryKey) {
    vPin = pin; delayMs = delayKey;
    vx = 0; vSum = 0;
    vd = vdx;
  }
  void loopRun() {
    vSum = 0.0f;
    for (int i = 0; i < 10; i++) {
      v[i] = analogRead(vPin);
      vSum += v[i];
      delay(delayMs);
    }
    vx = vSum * vd;
    vSum /=10.0f;
  }
} Battery;
Battery b1, b2, b3;
void Battery_Setup() {
  b1.init(A4, 20);
  b2.init(A5, 20);
  b3.init(A6, 20);
}
void Battery_loop() {
  b1.loopRun();
  b2.loopRun();
  b3.loopRun();
}
void Battery_log() {
  lg(b1.vSum); lg(','); lg(b2.vSum); lg(','); lg(b3.vSum); lg(','); //lg();
  lg(b1.vx); lg(','); lg(b2.vx); lg(','); lg(b3.vx); lg(','); lg();
}
void Battery_Lcd() {
  String s = "";
  s.concat(b1.vx);  s.concat(' ');
  s.concat(b2.vx);  s.concat(' ');
  s.concat(b3.vx);  s.concat(' ');
  LCD1602_Show(0, 0, s);
}

