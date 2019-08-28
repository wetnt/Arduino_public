
int pinLed = 13;
void setup() {
  Serial.begin(115200);
  oled_setup();
  moto_setup();
}

void loop() {
  //driveStepper();
  oled_loop(); delay(300);
}

void driveStepper() {
  moto_work();
}

