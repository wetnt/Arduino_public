//===============================================
#include <LiquidCrystal.h>
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);//lcd(RS,RW,EN,D4,5,6,7);
LiquidCrystal lcd(7,8,9,      6,5,4,3);//lcd(RS,RW,EN,D4,5,6,7);
//===============================================
//===============================================
void LCD1602_setup() {
  lcd.begin(16, 2);//columns and rows
  lcd.print(F("LCD1602_setup_OK!"));
  lg(F("LCD1602_setup_OK!")); lg();
  delay(200);
}
void LCD1602_Clear() {
  lcd.clear();
}
void LCD1602_Show(int x, int y, String t) {
  lcd.setCursor(x, y);
  lcd.print(t);
}
void LCD1602_loop_test() {
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}
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
