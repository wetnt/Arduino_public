//===============================================
//PIN1  GND/VSS 接0V
//PIN2  VCC/VDD 接4.8V-5V
//PIN3  V0  对地接电阻470-2K
//PIN4  RS RS=0，指令寄存器；RS=1，数据寄存器
//PIN5  R/W R/W=0，写；R/W=1，读
//PIN6  E  允许信号
//PIN11 D4 数据4
//PIN12 D5 数据5
//PIN13 D6 数据6
//PIN14 D7 数据7
//PIN15 LED+ 背光正极，接4.8V - 5V
//PIN16 LED- 背光负极，接0V
//LiquidCrystal(rs,rw,enable,d4,d5,d6,d7);
//===============================================

#include <LiquidCrystal.h>
LiquidCrystal lcd(10, 9, 8, 7, 6, 5, 4); //RS,RW,EN,D7654


void setup() {
  lcd.begin(128, 64);//columns and rows
  lcd.print("hello, world!");
}

void loop() {  
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("1234567890");
  lcd.setCursor(6,0);  lcd.print("1234567890");
  lcd.setCursor(12,0);  lcd.print("ABCEDSDFASDF");
  lcd.setCursor(24,0);  lcd.print("文");
  //lcd.print("www.commsat.com");
  //lcd.setCursor(2, 1); lcd.print("www.commsat.com");
  //lcd.setCursor(0, 2); lcd.print(millis());
  //lcd.print(millis()/1000);
  delay(100);
}
