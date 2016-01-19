//PCD8544 nokia = PCD8544(5, 6, 7, 8, 9); //SCLK,DIN,D/C,RST,CS
//  1. RST ——复位
//  2. CE  —— 片选
//  3. DC  —— 数据/指令选择
//  4. DIN —— 串行数据线
//  5. CLK —— 串行时钟线
//  6. VCC —— 电源输入（3.3v和5v均可，经过实验验证，没有问题）
//  7. BL  ——  背光控制端
//  8. GND —— 地线

#include <PCD8544.h>
static PCD8544 lcd;// = PCD8544(5, 6, 7, 9, 8);
void LcdSetup(int SCLK, int DIN, int DC, int RST, int CS, int DBD) {
  //-------------------------------------
  //lcd = PCD8544(5, 6, 7, 9, 8);
  lcd = PCD8544(SCLK, DIN, DC, RST, CS);
  //-------------------------------------
  lcd.begin(84, 48);
  lcd.setContrast(DBD);
  //-------------------------------------
  lcd.setCursor(0, 0);
  lcd.print("PCD8544.Setup!");
  //-------------------------------------
}
void LcdClear() {
  lcd.clear();
}
void LcdShow(int x, int y, String str) {
  lcd.setCursor(x, y);
  lcd.print(str);
}
void LcdTest() {
  static int counter = 0;
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print(counter, DEC);
  lcd.write(' ');
  lcd.write(0);

  lg(counter);
  lgln();
  counter++;
}

