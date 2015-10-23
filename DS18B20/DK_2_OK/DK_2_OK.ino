#include "Timer.h"
Timer t;
//--------------------------------------------
int ledPin = 13;
//--------------------------------------------
void setup(void)
{
  //--------------------------------------------
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  int tickEvent0 = t.every(5000, DS18B20_Run);
  int tickEvent1 = t.every(1000, Blink_Run);
  //--------------------------------------------
  DS18B20_setup();
  //DS18B20_setup_print();
  //--------------------------------------------
}
void loop(void)
{
  t.update();
}
//===============================================
void DS18B20_Run() {
  //--------------------------------------------
  DS18B20_loop();
  //DS18B20_loop_print();
  DS18B20_loop_print2();
  //--------------------------------------------
}
void Blink_Run() {
  //--------------------------------------------
  if ( DS18B20_Min_Key(30) && DS18B20_Max_Key(31)) {
    Blink_Flash(ledPin);
    Blink_Flash(ledPin);
    Blink_Flash(ledPin);
  }else{
    Blink_Stop(ledPin);
  }
  //--------------------------------------------
}
//===============================================



