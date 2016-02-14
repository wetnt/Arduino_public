typedef struct tLoop {
  unsigned long startTime = millis();
  unsigned long msKey = 1000;
  void init(unsigned long k) {
    msKey = k; startTime = millis();
  }
  boolean tloop() {
    if (millis() - startTime < msKey) return false;
    startTime = millis(); return true;
  }
} tLoop;
//===============================================
tLoop t1s, t2s, t5s, t10s, t20s;
void tLoop_Setup() {
  t1s.init(1 * 1000);
  t2s.init(2 * 1000);
  t5s.init(5 * 1000);
  t10s.init(10 * 1000);
  t20s.init(20 * 1000);
}
boolean t1s_loop() {
  return t1s.tloop();
}
boolean t2s_loop() {
  return t2s.tloop();
}
boolean t5s_loop() {
  return t5s.tloop();
}
boolean t10s_loop() {
  return t10s.tloop();
}
boolean t20s_loop() {
  return t20s.tloop();
}
//===============================================
