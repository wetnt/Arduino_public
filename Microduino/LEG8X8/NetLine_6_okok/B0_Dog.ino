//http://m.blog.csdn.net/article/details?id=50396518
#include <avr/wdt.h>
//WDTO_15MS/WDTO_30MS/WDTO_60MS
//WDTO_120MS/WDTO_250MS/WDTO_500MS
//WDTO_1S/WDTO_2S/WDTO_4S/WDTO_8S
void Dog_Start(){
  wdt_enable(WDTO_8S); //开启看门狗，并设置溢出时间为8秒
}
void Dog_Loop(){
  //lg("Dog_Loop()...");lg();
  wdt_reset(); //喂狗操作，使看门狗定时器复位
}

