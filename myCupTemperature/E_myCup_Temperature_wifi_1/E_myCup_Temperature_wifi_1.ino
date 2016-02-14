//--------------------------------------------
#include "Timer.h"
Timer t;
//--------------------------------------------
void setup(void)
{
  //--------------------------------------------
  lgsetup("My Cup Temperature!");
  //------------------------------------------
  int d[4] = {A1, A2, A3, A4}; //选位
  int p[8] = {2, 3, 4, 5, 6, 7, 8, 9}; //数码段
  Tube4_Init(d, p, 0);
  Tube4_set(-1, -1, -1, -1, 0);
  //--------------------------------------------
  Beep_Init(A5); Blink_Init(13);
  //--------------------------------------------
  DS18B20_Init();
  myCup_Init(55, 50, 45);
  //myCup_Init(30, 28, 26);
  //--------------------------------------------
  wifi_Init();
  //--------------------------------------------
  int tickEvent0 = t.every(5 * 1000, DS18B20_Run);
  int tickEvent1 = t.every(5 * 1000, TubeSetShow);
  int tickEvent2 = t.every(10 * 1000, myCupCheck);
  //int tickEvent3 = t.every(10 * 1000, Lewei_Loop);
  //--------------------------------------------
}
void loop(void) {
  t.update();
  Tube4_loop();
}
//===============================================
void DS18B20_Run() {
  DS18B20_loop(); DS18B20_print();
}
void TubeSetShow() {
  //------------------------------------------
  //char s[10];
  //snprintf(s, sizeof(s), "%d",k );
  //int n = sizeof(s);
  //------------------------------------------
  int k = GetMyCupTemperature();
  int a = k / 1000; if (a <= 0)a = -1;
  int b = k / 100; if (b <= 0)b = -1;
  int c = k / 10; if (c <= 0)c = -1;
  int d = k % 10;
  Tube4_set(a, b, c, d, 0);
  lg("k="); lg(k); lg(","); lg(a);  lg(","); lg(b); lg();
  //------------------------------------------
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    t.update();
    lgFeed();
    wfs_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
