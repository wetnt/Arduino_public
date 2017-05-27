typedef struct B_analogRead {
  int vPin = A0;
  int delayMs = 10;
  float vx, vSum;
  int v[10];
  void init(int pin, int delayKey) {
    vPin = pin; delayMs = delayKey;
    vx = 0; vSum = 0;
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
