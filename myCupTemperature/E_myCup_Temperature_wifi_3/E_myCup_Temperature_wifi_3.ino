//===============================================
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
  Beep_Init(A0); Blink_Init(13);
  //--------------------------------------------
  DS18B20_Init();
  myCup_Init(46, 43, 40, 38);
  //myCup_Init(30, 28, 26);
  //--------------------------------------------
  wifi_Init(); lewei_time_init();
  //--------------------------------------------
  tLoop_Setup();
  //--------------------------------------------
}
//===============================================
void loop(void) {
  //------------------------------------------
  work(); //smartDelay(10 * 1000);
  //------------------------------------------
  lgFeed(); wfs_loop(); Tube4_loop();
  //------------------------------------------
}
//===============================================
void work() {
  //------------------------------------------
  if (t5s_loop()) TubeTurn();
  if (t2s_loop()) {
    DS18B20_loop(); //DS18B20_print();
    myCupCheck();
  }
  if (t20s_loop()) {
    Lewei_Loop(); lewei_time_exp();
  }
  //------------------------------------------
}
boolean TubeShowKey = false;
void TubeTurn() {
  TubeShowKey = !TubeShowKey;
  if (TubeShowKey)
    TubeTemperatureShow();
  else
    lewei_time_show();
}
void TubeTemperatureShow() {
  //------------------------------------------
  //char s[10];snprintf(s, sizeof(s), "%d",k );
  //lg("k="); lg(k); lg(","); lg(a);  lg(","); lg(b); lg();
  //------------------------------------------
  int k = GetMyCupTemperature();
  int a = k / 1000; if (a <= 0)a = -1;
  int b = k / 100; if (b <= 0)b = -1;
  int c = k / 10; if (c <= 0)c = -1;
  int d = k % 10;
  Tube4_set(a, b, c, d, 0);
  //------------------------------------------
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); wfs_loop(); Tube4_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
