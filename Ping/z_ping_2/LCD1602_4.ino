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
//LiquidCrystal(rs,rw,enable,d4,d5,d6,d7);
//===============================================

#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 4, 5, 6, 7, 8, 9);

void LCD_setup() {
  lcd.begin(16, 2);//columns rows
  lcd.print("LCD start...!");
}
void lcd_show_float(int x, int y, float z) {
  lcd.setCursor(x, y);
  lcd.print(z);
}
void lcd_show_string(int x, int y, String z) {
  lcd.setCursor(x, y);
  lcd.print(z);
}
void lcd_clear() {
  lcd.clear();
}
