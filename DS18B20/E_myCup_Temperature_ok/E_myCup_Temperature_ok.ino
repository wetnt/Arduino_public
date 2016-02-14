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
  //--------------------------------------------
  int tickEvent0 = t.every(2000, DS18B20_Run);
  int tickEvent1 = t.every(5000, myCupCheck);
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
int myWaterTemperatureA = 55; boolean myWaterTemperatureAk = false;
int myWaterTemperatureB = 50; boolean myWaterTemperatureBk = false;
int myWaterTemperatureC = 45; boolean myWaterTemperatureCk = false;
void myCupCheck() {
  float t = GetMyCupTemperature();
  lg("myCupTemperature="); lg(t); lg();
  if (t > myWaterTemperatureA) myWaterTemperatureAk = true;
  if (t > myWaterTemperatureB) myWaterTemperatureBk = true;
  if (t > myWaterTemperatureC) myWaterTemperatureCk = true;
  if (myWaterTemperatureAk && t < myWaterTemperatureA) {
    Beep(10); myWaterTemperatureAk = false;
  }
  if (myWaterTemperatureBk && t < myWaterTemperatureB) {
    Beep(8); myWaterTemperatureBk = false;
  }
  if (myWaterTemperatureCk && t < myWaterTemperatureC) {
    Beep(5); myWaterTemperatureCk = false;
  }
}
//=======================================================================


