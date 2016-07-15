int PinBeep = 2;
void Beep_Setup() {
  pinMode(PinBeep, OUTPUT);
  digitalWrite(PinBeep, HIGH); //发声音
  Beep_Run();
}
void Beep_Run() {
  digitalWrite(PinBeep, LOW); //发声音
  smartDelay(200);//延时1ms
  digitalWrite(PinBeep, HIGH); //发声音
}

