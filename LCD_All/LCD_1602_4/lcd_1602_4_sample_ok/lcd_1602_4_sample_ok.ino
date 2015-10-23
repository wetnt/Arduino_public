//===============================================
//PIN1  GND 接0V
//PIN2  VCC 接4.8V-5V
//PIN3  V0  对地接电阻470-2K
//PIN4  RS RS=0，指令寄存器；RS=1，数据寄存器
//PIN5  R/W R/W=0，写；R/W=1，读
//PIN6  E  允许信号
//PIN7  D0 数据0
//PIN8  D1 数据1
//PIN9  D2 数据2
//PIN10 D3 数据3
//PIN11 D4 数据4
//PIN12 D5 数据5
//PIN13 D6 数据6
//PIN14 D7 数据7
//PIN15 LED+ 背光正极，接4.8V - 5V
//PIN16 LED- 背光负极，接0V
//LiquidCrystal(rs,rw,enable,d0,d1,d2,d3);
//===============================================

#include <LiquidCrystal.h>
//LiquidCrystal lcd(7, 8, 9, 6, 5, 4, 3);//RS,RW,EN,D6543
//LiquidCrystal lcd(11, 10, 9, 8, 7, 6, 5);
//LiquidCrystal lcd(11, 10, 9, 5, 6, 7, 8);
//LiquidCrystal lcd(8, 7, 6, 5, 4, 3,2);
//LiquidCrystal lcd(6,7,8, 5, 4,3,2);
//LiquidCrystal lcd(A2,A1,A0,8, 7,6,5);
//LiquidCrystal lcd(7,8,9,5,4,3,2);
//LiquidCrystal lcd(A6,A5,A4,A3,A2,A1,A0);
//LiquidCrystal lcd(A4,A5,A6,A3,A2,A1,A0);
//LiquidCrystal lcd(A6,A5,A4,A0,A1,A2,A3);
//LiquidCrystal lcd(A6,A5,A4,A3,A2,A1,A0);
LiquidCrystal lcd(13,A5,A4,A3,A2,A1,A0);
//LiquidCrystal lcd(2,3,4,5,6,7,8);

void setup() {
  lcd.begin(16, 2);//columns and rows
  lcd.print("hello, world!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  delay(1000);
}
