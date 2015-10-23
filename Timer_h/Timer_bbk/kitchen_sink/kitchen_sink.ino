#include "Timer.h"

Timer t;

int ledEvent;

void setup()
{
  Serial.begin(9600);
  int tickEvent = t.every(2000, doSomething);
  Serial.print("A id=");
  Serial.println(tickEvent);
  
  pinMode(13, OUTPUT);
  ledEvent = t.oscillate(13, 50, HIGH);
  Serial.print("B id=");
  Serial.println(ledEvent);
  
  int afterEvent = t.after(10000, doAfter);
  Serial.print("C id=");
  Serial.println(afterEvent); 
  
}

void loop()
{
  t.update();
}

void doSomething()
{
  Serial.print("A: millis()=");
  Serial.println(millis()/1000);
}


void doAfter()
{
  Serial.println("C stop the led event");
  t.stop(ledEvent);
  t.oscillate(13, 500, HIGH, 5);
}
