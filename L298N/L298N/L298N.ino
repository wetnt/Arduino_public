// motor A
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 4;

unsigned long time;
int speed;
int dir;

void setup() {
  Serial.begin(9600);
  
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);

  time = millis();
  speed = 0;
  dir = 1;
}

void loop() {  
  speed += 1;
    if (speed > 255) {
      speed = 0;
  }
  Serial.print("B id=");
  Serial.println(speed);
  
  
  
  analogWrite(speedPinA, speed);
  // set direction
  if (1 == dir) {
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
  } else {
    digitalWrite(dir1PinA, HIGH);
    digitalWrite(dir2PinA, LOW);
  }
  if (millis() - time > 25000)  {
    time = millis();
    if (1 == dir) {
      dir = 0;
    } else {
      dir =1;
    }
    speed = 100;
  }
  delay(100);
}
