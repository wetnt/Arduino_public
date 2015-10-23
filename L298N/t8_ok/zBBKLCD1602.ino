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
//LiquidCrystal lcd(8,7,6,5,4,3,2);
LiquidCrystal lcd(23,27,29,31,33,35,37);
//------------------------------------------
long LCDTime = millis(), LCDTimeKey = 1000;
//------------------------------------------
void LCD_Setup() {
  lcd.begin(16, 2);//columns,rows/列行
  lcd.print("BBKOK!");
  //Serial.println("BBKOK!");
}
void LCD_Loop(bool showkey){
  //---------------------------------------
  if( millis() - LCDTime < LCDTimeKey) return; 
  LCDTime = millis();
  //---------------------------------------
  LCD_Show_AVW(showkey);
  //---------------------------------------
}
void LCD_Show_AVW(bool showkey){
  //----------------------------------------------------------------------------------------------
  //String t = ""; t.concat(thour); t.concat(":"); t.concat(tmint); t.concat(":"); t.concat(tsecd);
  //t.concat(' ');t.concat((int)DHT_WD); t.concat("c ");t.concat((int)DHT_SD); t.concat('%');
  String a = ""; a.concat("p="); a.concat(cm); a.concat(" "); a.concat("A="); a.concat("");
  String b = ""; 
  b.concat(CMD_FB); b.concat(' '); 
  b.concat(CMD_YW); b.concat(' '); 
  b.concat(CMD_PW); b.concat(' '); 
  b.concat(CMD_RL);
  //----------------------------------------------------------------------------------------------  
  lcd.clear();
  lcd.setCursor(0,0);     lcd.print(a);
  lcd.setCursor(0,1);     lcd.print(b);
  //----------------------------------------------------------------------------------------------
}
