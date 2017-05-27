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
tLoop t1s, t2s, t5s, t10s, t20s, t30s;
void tLoop_Setup() {
  t1s.init(1 * 1000);
  t2s.init(2 * 1000);
  t5s.init(5 * 1000);
  t10s.init(10 * 1000);
  t20s.init(20 * 1000);
  t30s.init(30 * 1000);
}
boolean ts_loop(int x) {
  switch (x) {
    case 1:  return t1s.tloop();  break;
    case 2:  return t2s.tloop();  break;
    case 5:  return t5s.tloop();  break;
    case 10: return t10s.tloop(); break;
    case 20: return t20s.tloop(); break;
    case 30: return t30s.tloop(); break;
  }
  return false;
}
//===============================================
