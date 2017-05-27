#include <Servo.h>
Servo servo1;
int val;
int runkey = 10;
void setup() {
  Serial.begin(115200);
  servo1.attach(4);//舵機一接pin4
}

void loop() {
  if (val >= 180) runkey = -10;
  if (val <= 0) runkey = 10;
  val = val + runkey;
  if(val<0)val=0;
  if(val>180)val=180;
  servo1.write(val); Serial.println(val);
  delay(500);
}
