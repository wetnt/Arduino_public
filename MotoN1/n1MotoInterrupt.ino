//---------------------------------------------------------------
volatile long count_r = 0;
volatile long count_l = 0;
//---------------------------------------------------------------
void MotoInterruptSetup() {
  attachInterrupt(1, rencoder_r, CHANGE);
  attachInterrupt(0, rencoder_l, CHANGE);
}
void rencoder_r()     //Interrupt:record counter-Right
{
  count_r++;
}
void rencoder_l()     //Interrupt:record counter-Left
{
  count_l++;
}
//---------------------------------------------------------------
void MotoInterruptStart() {
  interrupts();
}
void MotoInterruptStop() {
  noInterrupts();
}
//---------------------------------------------------------------
