int pinA = A0;
void setup() {
  Serial.begin(115200);
}
int v[10];
void loop() {
  float s = 0.0f;
  for (int i = 0; i < 10; i++) {
    v[i] = analogRead(pinA);
    s += v[i];
    delay(50);
  }
  s /= 10.0f;
  //s = s*4.76f*993/216/1023;
  s*=0.0266f;
  Serial.println(s);
}
