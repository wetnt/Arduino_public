//整理者：极客工坊bg1lsy (lsy@sogou.com)
//整理时间：2013.05.25
#include <SPI.h>
#include <RFID.h>
/*
RFID   ->   Arduino UNO
-------------------
3.3V   ->  3.3V
RST   ->  D5
GND   ->  GND
IRQ   ->  NC
MISI  ->  D12
MOSI  ->  D11
SCK   ->  D13
SDA   ->  D10
注意：上面接线方法只适用UNO或跟UNO兼容的硬件SPI接口的板卡，
对LEONARDO这种板，因为SPI接口没接到IO口，上面的接线方法不适用
Leonardo板接法如下：
RFID         leonado  ICSP接口
-------------------
3.3V   ->  3.3V
RST   ->   D5
GND   ->  ICSP 6脚
IRQ   ->   NC
MISI  ->  ICSP 1脚
MOSI  ->  ICSP 4脚
SCK   ->  ICSP 3脚
SDA   ->  D10
*/
RFID rfid(10,5);   //D10--读卡器MOSI引脚、D5--读卡器RST引脚
//那个读写的例子第6行注释写错了，D10应该连SS片选。D10-->SS, D11-->MOSI, D12 -->MISO, D13 -->SCK，D5 -->RST。
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  //Keyboard.begin();
  rfid.init();
}

void loop()
{
  //找卡
  if (rfid.isCard()) {
    Serial.println("Find the card!");
    //读取卡序列号
    if (rfid.readCardSerial()) {
      Serial.print("The card's number is  : ");
      Serial.print(rfid.serNum[0],HEX);
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(rfid.serNum[3],HEX);
      Serial.print(rfid.serNum[4],HEX);
      Serial.println(" ");
    }
    //选卡，可返回卡容量（锁定卡片，防止多数读取），去掉本行将连续读卡
    rfid.selectTag(rfid.serNum);
  }
  keyPress();
  rfid.halt();
  
}


void keyPress(){
//Keyboard.press('a');
}
