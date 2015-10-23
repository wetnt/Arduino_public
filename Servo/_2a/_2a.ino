#include <Servo.h> 
Servo servo1,servo2,servo3;

void setup()
{
  Serial.begin(9600);
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo1.write(75);
  servo2.write(75);
  servo3.write(75);
  delay(20000);
}

void loop()
{

  for (int i = 0; i <= 15; i++)
  {
    int val = i*10;
    servo1.write(val);
    servo2.write(val);
    servo3.write(val);
    Serial.println(val);
    delay(200);
  } 
  for (int i = 15; i >= 0; i--)
  {
    int val = i*10;
    servo1.write(val);
    servo2.write(val);
    servo3.write(val);
    Serial.println(val);
    delay(200);
  } 
}




