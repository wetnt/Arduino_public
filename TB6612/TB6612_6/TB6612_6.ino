
int pinLed = 13;
void setup() {
  Serial.begin(115200);
  moto_setup();
}

void loop() {
  driveStepper();
}



void driveStepper() {
moto_work();
}

