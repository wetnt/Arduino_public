#include <avr/wdt.h>
void setup()
{
  //------------------------------------------
  Serial.begin(115200);
  while (!Serial){
    ;
  };
  Serial.println("WatchDog_Start......");
  //------------------------------------------
  pinMode(13,OUTPUT);
  wdt_enable(WDTO_8S); //开启看门狗，并设置溢出时间为8秒
  //------------------------------------------
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  delay(100);
  digitalWrite(13,HIGH);
  delay(100);
  digitalWrite(13,LOW);
  delay(100);
}

void loop()
{
  digitalWrite(13,HIGH);
  delay(600);
  digitalWrite(13,LOW);
  delay(600);
  //------------------------------------------
  Serial.println("wdt_reset......");
  wdt_reset(); //喂狗操作，使看门狗定时器复位
  //------------------------------------------
  while (true){
    Serial.println("delay......");
    delay(1000);
  };
  //------------------------------------------
}


