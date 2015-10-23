void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("Waiting for GPS time ... ");
}

void loop() {
  while (Serial.available()) {
    Serial.write(Serial.read());
  }
}
