
unsigned long time;
int speed;
int dir;

void setup() {
  Serial.begin(9600);
  BKMOTO(4,5,6,7,8,9);
  time = millis();
  speed = 0;
  dir = 1;
  Code_setIn();
}

void loop() {
  //-----------------------
  speed += 1;
  if (speed > 255) {
    speed = 255;
  }
  //-----------------------  
  //  Serial.print(count_right);
  //  Serial.print("-");
  //  Serial.print(count_lefts);
  //  Serial.print("-");
  //  Serial.print(nx);
  //  Serial.println();
  //-----------------------  
  if (1 == dir) 
    RunF(speed);
  else 
    RunB( speed);
  //-----------------------  
  if (millis() - time > 2000)  {
    //-----------------------  
    time = millis();
    //-----------------------  
    if (1 == dir)
      dir = 0;
    else
      dir = 1;
    //-----------------------  
    speed = 0;
    Code_Clear();
    //-----------------------  
  }
  //-----------------------  
  delay(5);
  //-----------------------  
}






