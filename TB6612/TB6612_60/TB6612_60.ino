int pinLed = 13;
void setup() {
  Serial.begin(115200);
  oled_loop();
  moto_setup();
}

void loop() {
  driveStepper();
}

void driveStepper() {
  moto_work();
}

