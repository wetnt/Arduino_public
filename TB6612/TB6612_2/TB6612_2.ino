//TB6612

int PWMA = 3;
int AIN1 = 7;
int AIN2 = 8;
int STBY = 4;

int pinLed = 13;
void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  driveStepper(); delay(2000);
  stopStepper(); delay(2000);
}

void stopStepper() {
  digitalWrite(STBY, LOW);
}


void driveStepper() {
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  for (int i = 0; i < 255; i++) {
    analogWrite(PWMA, i);
    Serial.println(i);
    delay(100);
  }

  delay(2000);
  digitalWrite(STBY, LOW);
  delay(2000);


  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH );

  for (int i = 0; i < 255; i++) {
    analogWrite(PWMA, i);
    Serial.println(i);
    delay(100);
  }
  delay(2000);

}

