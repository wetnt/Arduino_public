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
LiquidCrystal lcd(8,7,6,5,4,3,2);
//------------------------------------------
long LCDTime = millis(), LCDTimeKey = 1000;
//------------------------------------------
void LCD_Setup() {
  Serial.print("BBKLcd_Setup......");
  lcd.begin(16, 2);//columns and rows
  lcd.print("BBKLcd_Setup_OK!");
  Serial.println("OK!");   
}
void LCD_Show(char *a,char *b,bool showkey) {
  //---------------------------------------
  lcd.clear();
  lcd.setCursor(0,0);   
  lcd.print(a);
  lcd.setCursor(0,1);   
  lcd.print(b);
  //---------------------------------------
  if(showkey){
    Serial.println(a);   
    Serial.println(b);   
  }
  //---------------------------------------
}
void LCD_Loop(bool showkey){
  //---------------------------------------
  if( millis() - LCDTime < LCDTimeKey) return; 
  LCDTime = millis();
  //---------------------------------------
  LCD_Show_AVW(showkey);
  //---------------------------------------
}
void LCD_ShowTest() {
  //---------------------------------------
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  //---------------------------------------
}
char lcd_a[17], lcd_b[17];
char floatStringAmps[3];
char floatStringKwhs[7];
void LCD_Show_AVW(bool showkey){
  //---------------------------------------
  if(1){
    //---------------------------------------
    dtostrf(Amps, 3, 1, floatStringAmps);
    dtostrf(Kwhs, 7, 1, floatStringKwhs);
    snprintf(lcd_a, 18, "Time: %02d:%02d:%02d", time_hourss,time_minute,time_second);
    //snprintf(lcd_b, 16, "W= %d A= %s", Watt,floatStringAmps);
    //snprintf(lcd_b, 18, "V= %d K= %s", Volt,floatStringKwhs);    
    snprintf(lcd_b, 18, "%d %d %s %s", Watt,Volt,floatStringAmps,floatStringKwhs);
    
    LCD_Show(lcd_a,lcd_b,true);
    //---------------------------------------
  }
  else{
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
    if(showkey){
      Serial.println(sa);   
      Serial.println(sb);  
      Serial.println(sc);   
    }
    //---------------------------------------
  }
  //---------------------------------------
}








