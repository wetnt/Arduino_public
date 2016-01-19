//==========================================================
double Output = 0;
int pAIn = 3, pBIn = 2;
int count_right = 0, count_lefts = 0;
//==========================================================
void Interrupt_right_run() {
  if (Output >= 0) count_right += 1; else count_right -= 1;
}
void Interrupt_lefts_run() {
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
