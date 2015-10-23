//BBKMOTO mt;
unsigned long time;
int speed;
int dir;



void setup() {
  Serial.begin(9600);
  
  mt.BBKMOTOS(0,0,0,2,3,4);

  time = millis();
  speed = 0;
  dir = 1;
}

void loop() {  
  speed += 1;
    if (speed > 255) {
      speed = 100;
  }
  Serial.print("B id=");
  Serial.println(speed);
  
  mt.MotoRun();
  
  analogWrite(speedPinA, speed);
  // set direction
  if (1 == dir) {
    mt.MotoRun(1,speed);
  } else {
    mt.MotoRun(-1,speed);
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
