void setup() {
  Serial.begin(115200);
  DHT_setup();
}
void loop() {
  DHT_loop();
  DHT_show();
  delay(1000);
}
