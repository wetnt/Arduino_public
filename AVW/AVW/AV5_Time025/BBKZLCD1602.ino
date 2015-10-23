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
//LiquidCrystal lcd(2,3,4,5,6,7,8);
LiquidCrystal lcd(8,7,6,5,4,3,2);


void LCD_Setup() {
  lcd.begin(16, 2);//columns and rows
  lcd.print("BBKLcd_Setup_OK!");
  Serial.println("BBKLcd_Setup_OK!");   
}

void LCD_Loop() {
  //---------------------------------------
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  //---------------------------------------
}

void LCD_Show(char *a,char *b) {
  //---------------------------------------
  lcd.clear();
  lcd.setCursor(0,0);   
  lcd.print(a);
  lcd.setCursor(0,1);   
  lcd.print(b);
  //---------------------------------------
}
char lcd_a[17], lcd_b[17];
char floatString[4];
void LCD_AVW_Show(){
  //---------------------------------------
//  dtostrf(Amps, 4, 1, floatString);
//  snprintf(lcd_a, 16, "Time: %02d:%02d:%02d", time_hourss,time_minute,time_second);
//  //snprintf(lcd_b, 16, "W= %d A= %s", Watt,floatString);
//  snprintf(lcd_b, 18, "V= %d K= %d", Volt,Kwhs);
//  LCD_Show(lcd_a,lcd_b);
  //---------------------------------------
  lcd.clear();
  String sa = String("W=") + String(Watt) + String(" ") + String("A=") + String(Amps);
  String sb = String("V=") + String(Volt) + String(" ") + String("K=") + String(Kwhs);
  String sc = String(time_hourss) + String(":") + String(time_minute) + String(":") + String(time_second);
  lcd.setCursor(0,0);   
  lcd.print(sc);
  lcd.setCursor(0,1);   
  lcd.print(sb);  
  //---------------------------------------
}


