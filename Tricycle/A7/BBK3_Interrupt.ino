//==========================================================
double Output = 0;
int pAIn = 3, pBIn = 2;
int count_right = 0, count_lefts = 0;
int speed_right = 0, speed_lefts = 0;
int speed_right_min = 1000, speed_lefts_min = 1000;
unsigned long time_right = millis(), time_lefts = millis();
//==========================================================
void Interrupt_right_run() {
  speed_right = millis() - time_right; time_right = millis();
  if (speed_right_min > speed_right) speed_right_min = speed_right;
  if (Output >= 0) count_right += 1; else count_right -= 1;
}
void Interrupt_lefts_run() {
  speed_lefts = millis() - time_lefts; time_lefts = millis();
  if (speed_lefts_min > speed_lefts) speed_lefts_min = speed_lefts;
  if (Output >= 0) count_lefts += 1; else count_lefts -= 1;
}
void Interrupt_setIn() {
  attachInterrupt(pAIn, Interrupt_right_run, FALLING);
  attachInterrupt(pBIn, Interrupt_lefts_run, FALLING);
}
void Interrupt_Clear() {
  count_right = 0; count_lefts = 0;
}
//==========================================================
