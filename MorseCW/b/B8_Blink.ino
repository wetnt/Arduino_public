//===============================================
int ledPin = 13;
//===============================================
void Blink_Init(int pin) {
  lgln(F("Blink_Init..."));
  ledPin = pin; pinMode(ledPin, OUTPUT);
  Blink(3); Blink_Stop();
}
void Blink_Start() {
  digitalWrite(ledPin, HIGH);
}
void Blink_Stop() {
  digitalWrite(ledPin, LOW);
}
void Blink_Flash() {
  Blink_Start(); delay(50);
  Blink_Stop();  delay(50);
}
void Blink(int n) {
  lg(F("Blink_loop = ")); lg(n); lg();
  for (int i = 0; i < n; i++) Blink_Flash();
  Blink_Stop();
}
//===============================================


