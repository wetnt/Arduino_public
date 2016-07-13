//===============================================
void setup(void) {
  //--------------------------------------------
  lgsetup("My Cup Temperature!");
  //------------------------------------------
  int d[4] = {A1, A2, A3, A4}; //选位
  int p[8] = {2, 3, 4, 5, 6, 7, 8, 9}; //数码段
  Tube4_Init(d, p, 0);
  Tube4_set(-1, -1, -1, 0, 0);
  //--------------------------------------------
  Tube4_set(-1, -1, -1, 1, 0);
  Beep_Init(A0); Blink_Init(13);
  //--------------------------------------------
  Tube4_set(-1, -1, -1, 2, 0);
  DS18B20_Init();
  myCup_Init(46, 43, 40, 38);
  //--------------------------------------------
  Tube4_set(-1, -1, -1, 3, 0);
  wifi_Init(true, false, true); //lg,testAP,joinAP
  //--------------------------------------------
  Tube4_set(-1, -1, -1, 5, 0);
  tLoop_Setup();
  //--------------------------------------------
  Tube4_set(-1, -1, -1, 6, 0);//开始实际运行
  DS18B20_loop(); myCupCheck(); TubeTemperatureShow();
  Lewei_Loop(); lewei_time_exp(); lewei_time_show();
  //--------------------------------------------
}
//===============================================
void loop(void) {
  //------------------------------------------
  work(); //smartDelay(10 * 1000);
  //------------------------------------------
  lgFeed(); Tube4_loop();
  //------------------------------------------
}
//===============================================
void work() {
  //------------------------------------------
  if (ts_loop(2)) {
    TubeTurn();
    DS18B20_loop(); //DS18B20_print();
    myCupCheck();
  }
  if (ts_loop(30)) {
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
  //------------------------------------------
  int k = GetMyCupTemperature();
  int a = k / 1000; if (a <= 0)a = -1;
  int b = k / 100; if (b <= 0)b = -1;
  int c = k / 10; if (c <= 0)c = -1;
  int d = k % 10;
  Tube4_set(a, b, c, d, 0);
  lg("k="); lg(k); lg(","); lg(a);  lg(","); lg(b); lg(","); lg(c);  lg(","); lg(d); lg();
  //------------------------------------------
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); Tube4_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
