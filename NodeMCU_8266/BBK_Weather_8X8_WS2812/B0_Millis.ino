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
tLoop t1s, t2s, t5s, t10s, t20s, t30s, t60s, t100ms, t150ms, t200ms;
void tLoop_Setup() {
  //------------------------------------------
  t1s.init(1 * 1000);
  t2s.init(2 * 1000);
  t5s.init(5 * 1000);
  t10s.init(10 * 1000);
  t20s.init(20 * 1000);
  t30s.init(30 * 1000);
  t60s.init(60 * 1000);
  //------------------------------------------
  t100ms.init(100);
  t150ms.init(150);
  t200ms.init(200);
  //------------------------------------------
}
boolean ts_loop(int x) {
  switch (x) {
    //------------------------------------------
    case 1:  return t1s.tloop();  break;
    case 2:  return t2s.tloop();  break;
    case 5:  return t5s.tloop();  break;
    case 10: return t10s.tloop(); break;
    case 20: return t20s.tloop(); break;
    case 30: return t30s.tloop(); break;
    case 60: return t60s.tloop(); break;
    //------------------------------------------
    case 100: return t100ms.tloop(); break;
    case 150: return t150ms.tloop(); break;
    case 200: return t200ms.tloop(); break;
      //------------------------------------------
  }
  return false;
}
//===============================================
