//===============================================
void setup(void)
{
  //--------------------------------------------
  lgsetup("My Cup Temperature!");
  //--------------------------------------------
  DS18B20_Init();
  myCup_Init(46, 43, 40, 38);
  //--------------------------------------------
  wifi_Init(true,true, false); //lg,testAP,joinAP
  //--------------------------------------------
  lewei_time_init();
  //--------------------------------------------
  tLoop_Setup();
  //--------------------------------------------
  //DS18B20_loop(); myCupCheck(); TubeTemperatureShow();
  Lewei_Loop(); //lewei_time_exp(); lewei_time_show();
  //--------------------------------------------
}
//===============================================
void loop(void) {
  //------------------------------------------
  work(); //smartDelay(10 * 1000);
  //------------------------------------------
  lgFeed(); //wfs_loop(); //Tube4_loop();
  //------------------------------------------
}
//===============================================
void work() {
  //------------------------------------------
  if (ts_loop(2)) {
    //TubeTurn();
    //DS18B20_loop(); //DS18B20_print();
    //myCupCheck();
  }
  if (ts_loop(30)) {
    Lewei_Loop(); //lewei_time_exp();
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
  //  int k = GetMyCupTemperature();
  //  int a = k / 1000; if (a <= 0)a = -1;
  //  int b = k / 100; if (b <= 0)b = -1;
  //  int c = k / 10; if (c <= 0)c = -1;
  //  int d = k % 10;
  //  Tube4_set(a, b, c, d, 0);
  //lg("k="); lg(k); lg(","); lg(a);  lg(","); lg(b); lg(","); lg(c);  lg(","); lg(d); lg();
  //------------------------------------------
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); //Tube4_loop(); //wfs_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
