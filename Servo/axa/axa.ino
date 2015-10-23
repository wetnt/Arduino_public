#include <Servo.h> 
Servo servo1,servo2,servo3;

void setup()
{
  Serial.begin(9600);
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
}

void loop()
{
    servo1.write(75);
    servo2.write(75);
    servo3.write(75);
    delay(20000);
}



