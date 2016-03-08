
int Pinx[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
void setup() {
  for (int i = 0; i < 8; i++)pinMode(Pinx[i], INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);delay(200);
  digitalWrite(13, LOW);delay(200);
  digitalWrite(13, HIGH);delay(200);
  digitalWrite(13, LOW); delay(200);
  digitalWrite(13, LOW);  
  delay(1000);
}
