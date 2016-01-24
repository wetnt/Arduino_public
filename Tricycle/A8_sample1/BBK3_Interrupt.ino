//==========================================================
//http://www.arduino.cn/thread-2421-1-1.html
int pRIn = 0, pLIn = 1;//此处是终端号，不是IO
unsigned int intR, intL;
//==========================================================
void Interrupt_right_run() {
  intR++;
}
void Interrupt_lefts_run() {
  intL++;
}
void Interrupt_setIn() {
  attachInterrupt(pRIn, Interrupt_right_run, FALLING);
  attachInterrupt(pLIn, Interrupt_lefts_run, FALLING);
  lg("Interrupt_FALLING"); lg();
}
void Interrupt_clear_R() {
  intR = 0;
}
void Interrupt_clear_L() {
  intL = 0;
}
//==========================================================
