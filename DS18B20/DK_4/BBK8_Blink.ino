//===============================================
int ledPin = 13;
//===============================================
void Blink_Init(int pin) {
  lgln(F("Blink_Init..."));
  ledPin = pin; Blink_loop(3); Blink_Stop();
}
void Blink_Stop() {
  digitalWrite(ledPin, LOW);
}
void Blink_Flash() {
  digitalWrite(ledPin, HIGH); delay(50);
  digitalWrite(ledPin, LOW);  delay(50);
  digitalWrite(ledPin, LOW);
}
void Blink_loop(int n) {
  lgln(F("Blink..."));
  for (int i = 0; i < n; i++) Blink_Flash();
  Blink_Stop();
}
//===============================================


