// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//PCD8544 nokia = PCD8544(7, 6, 5, 4, 3);
//PCD8544 nokia = PCD8544(5, 6, 7, 8, 9); //SCLK,DIN,D/C,CS,RST

//  1. RST ——复位
//  2. CE  —— 片选
//  3. DC  —— 数据/指令选择
//  4. DIN —— 串行数据线
//  5. CLK —— 串行时钟线
//  6. VCC —— 电源输入（3.3v和5v均可，经过实验验证，没有问题）
//  7. BL  ——  背光控制端
//  8. GND —— 地线
  
#include <PCD8544.h>
static PCD8544 lcd = PCD8544(5, 6, 7, 8, 9);
//static PCD8544 lcd = PCD8544( 6, 7, 8, 9,10);
void setup() {
  //-------------------------------------
  Log_setup();
  //APC220_setup();
  //-------------------------------------
  lcd.begin(84, 48);
  lcd.setContrast(50);  
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  //-------------------------------------
}


void loop() {
  static int counter = 0;
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print(counter, DEC);
  lcd.write(' ');
  lcd.write(0);

  lg(counter);
  lgln();

  delay(500);
  counter++;
}

