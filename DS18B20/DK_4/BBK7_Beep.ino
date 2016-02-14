int beepPin = 3;
void Beep_Init(int pin) {
  lgln(F("Beep_Init..."));
  beepPin = pin; pinMode(beepPin, OUTPUT); BeepStop();
}
void Beep_Start() {
  digitalWrite(beepPin, LOW);
}
void Beep_Stop() {
  digitalWrite(beepPin, HIGH);
}
void Beep_Run() {
  //lgln(F("Beep"));
  Beep_Start(); delay(50);
  Beep_Stop();  delay(50);
}
void Beep_loop(int n) {
  lgln(F("Beep_loop..."));
  for (int i = 0; i < n; i++) Beep_Run();
  Beep_Stop();
}
