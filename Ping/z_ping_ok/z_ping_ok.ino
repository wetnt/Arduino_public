float len = 0;
void setup() {
  Serial.begin(115200);
  PingSetup(A0, A1);
}

void loop() {
  //--------------------------------------------------------
  len = PingLoop();
  delay(100);
  //--------------------------------------------------------
}