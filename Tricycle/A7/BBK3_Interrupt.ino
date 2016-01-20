//==========================================================
//http://www.arduino.cn/thread-2421-1-1.html
double Output = 0;
int pAIn = 1, pBIn = 0;//此处是终端号，不是IO
//int count_right = 0, count_lefts = 0;
//int speed_right = 0, speed_lefts = 0;
//int speed_right_min = 1000, speed_lefts_min = 1000;
unsigned long time_right = millis(), time_lefts = millis();
unsigned long time_right = millis(), time_lefts = millis();
//==========================================================
double spdr = 0, spdl = 0;
//==========================================================
void Interrupt_right_run() {
  //lg("Interrupt_right_run");lg();
  //if (Output >= 0) count_right += 1; else count_right -= 1;
  //if (speed_right_min > speed_right) speed_right_min = speed_right;
  speed_right = millis() - time_right; time_right = millis();
  spdr = 22.5 / speed_right;
}
void Interrupt_lefts_run() {
  //lg("Interrupt_lefts_run");lg();
  speed_lefts = millis() - time_lefts; time_lefts = millis();
  if (speed_lefts_min > speed_lefts) speed_lefts_min = speed_lefts;
  if (Output >= 0) count_lefts += 1; else count_lefts -= 1;
  spdl = 22.5 / speed_lefts;
}
void Interrupt_setIn() {
  attachInterrupt(pAIn, Interrupt_right_run, FALLING);
  attachInterrupt(pBIn, Interrupt_lefts_run, FALLING);
}
void Interrupt_Clear() {
  count_right = 0; count_lefts = 0;
}
//==========================================================
