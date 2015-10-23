
unsigned long time;
int speed;
int dir;



void setup() {
  Serial.begin(9600);
  BKMOTO(2,3,4,5,6,7);
  time = millis();
  speed = 0;
  dir = 1;
}

void loop() {
  //-----------------------
  speed += 1;
  if (speed > 255) {
    speed = 255;
  }
  Serial.print("B id=");
  Serial.println(speed);
  //-----------------------  
  if (1 == dir) {
    MotoRunA(1,speed);
    MotoRunB(1,speed);
  } 
  else {
    MotoRunA(-1,speed);
    MotoRunB(-1,speed);
  }
  //-----------------------  
  if (millis() - time > 5000)  {
    time = millis();
    if (1 == dir) {
      dir = 0;
    } 
    else {
      dir =1;
    }
    speed = 0;
  }
  delay(10);
  //-----------------------  
}

