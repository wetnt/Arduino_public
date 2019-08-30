//TB6612

//int PWMA = 6;
//int AIN1 = 9;
//int AIN2 = 10;
//int STBY = 0;
//int BIN1 = 12;
//int BIN2 = 13;
//int PWMB = 11;

int PWMA = 3;
int AIN1 = 2;
int AIN2 = 4;
int STBY = 0;
int BIN1 = 7;
int BIN2 = 8;
int PWMB = 5;

int pinLed = 13;
void setup() {
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  driveStepper();
}

void stopStepper() {
  digitalWrite(STBY, LOW);
}

void driveStepper() {
  for (int i = 0; i < 255; i++) {
    moto_right( i, 1);
    moto_lefts( i, 1);
    Serial.println(i);
    delay(50);
  }
  delay(5000);
  digitalWrite(STBY, LOW);
  delay(5000);
    for (int i = 0; i < 255; i++) {
    moto_right( i, -1);
    moto_lefts( i, -1);
    Serial.println(i);
    delay(50);
  }
  delay(5000);
  digitalWrite(STBY, LOW);
  delay(5000);
//  for (int i = 0; i < 255; i++) {
//    moto_right( i, -1);
//    moto_lefts( i, -1);
//    Serial.println(i);
//    delay(200);
//  }
//  delay(5000);
//  digitalWrite(STBY, LOW);
//  delay(5000);
//  for (int i = 0; i < 255; i++) {
//    moto_right( i, 1);
//    moto_lefts( i, -1);
//    Serial.println(i);
//    delay(200);
//  }
//  delay(5000);
//  digitalWrite(STBY, LOW);
//  delay(5000);
//  for (int i = 0; i < 255; i++) {
//    moto_right( i, -1);
//    moto_lefts( i, 1);
//    Serial.println(i);
//    delay(200);
//  }
//  delay(5000);
//  digitalWrite(STBY, LOW);
//  delay(5000);
}

void moto_lefts(int v, int f) {
  if (f == 0) {
    digitalWrite(STBY, LOW);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW );
  } else if (f == 1) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH );
  } else if (f == -1) {
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW );
  }
  analogWrite(PWMA, v);
}
void moto_right(int v, int f) {
  if (f == 0) {
    digitalWrite(STBY, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW );
  } else if (f == 1) {
    digitalWrite(STBY, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH );
  } else if (f == -1) {
    digitalWrite(STBY, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW );
  }
  analogWrite(PWMB, v);
}

