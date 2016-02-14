//===============================================
int beepPin = 3;
//===============================================
void Beep_Init(int pin) {
  lgln(F("Beep_Init..."));
  beepPin = pin; pinMode(beepPin, OUTPUT);
  Beep(1); Beep_Stop();
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
void Beep(int n) {
  lg(F("Beep_loop = "));lg(n); lg();
  for (int i = 0; i < n; i++) Beep_Run();
  Beep_Stop();
}
