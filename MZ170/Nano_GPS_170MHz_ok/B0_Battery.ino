typedef struct B_analogRead {
  int vPin = A0;
  int delayMs = 20;
  float vx, vSum;
  int v[10];
  void init(int pin, int delayKey) {
    vPin = pin; delayMs = delayKey;
    vx = 0; vSum = 0;
    pinMode(vPin, INPUT);
  }
  void loopRun() {
    vSum = 0.0f;
    for (int i = 0; i < 10; i++) {
      v[i] = analogRead(vPin);
      vSum += v[i];
      smartDelay(delayMs);
    }
    vSum /= 10.0f;
  }
} B_analogRead;
B_analogRead pinV;
void B_analogRead_Setup() {
  pinV.init(A1, 10);
}
void B_analogRead_loop() {
  pinV.loopRun();
}
void B_analogRead_log() {
  lg(pinV.vSum); lg();
}

