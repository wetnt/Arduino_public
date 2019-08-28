float vBatt, voltAve = 3.7;


void Battery_setup() {
  Battery_loop();
}
void Battery_loop() {
  vBatt = M5.Axp.GetVbatData() * 1.1 / 1000;
  Serial.printf("%4.2fv ", vBatt);
}
