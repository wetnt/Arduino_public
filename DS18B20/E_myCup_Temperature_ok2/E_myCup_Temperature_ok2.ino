//--------------------------------------------
#include "Timer.h"
Timer t;
//--------------------------------------------
void setup(void)
{
  //--------------------------------------------
  lgsetup("My Cup Temperature!");
  //--------------------------------------------
  Beep_Init(3); Blink_Init(13);
  //--------------------------------------------
  DS18B20_Init();
  myCup_Init(55, 50, 45);
  //myCup_Init(28, 26, 24);
  //--------------------------------------------
  int tickEvent0 = t.every(5 * 1000, DS18B20_Run);
  int tickEvent1 = t.every(10 * 1000, myCupCheck);
  //--------------------------------------------
}
void loop(void) {
  t.update();
}
//===============================================
void DS18B20_Run() {
  DS18B20_loop(); DS18B20_print();
}
//=======================================================================
