void setup() {
  Serial.begin(115200);
  //PingSetup(A0, A1);
  Ping_setup(3, 2); //Trig,Echo;
}

void loop() {
  //--------------------------------------------------------
  Ping_loop(); Ping_show();
  delay(200);
  //--------------------------------------------------------
}
