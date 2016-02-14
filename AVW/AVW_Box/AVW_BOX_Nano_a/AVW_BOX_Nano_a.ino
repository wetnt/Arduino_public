//-------------------------------------------------------------------------
#include <SoftwareSerial.h>
//-------------------------------------------------------------------------
SoftwareSerial gas(10, 11); // RX, TX
static const long GasBaud = 9600;
//-------------------------------------------------------------------------
SoftwareSerial wfs(9, 8); // RX, TX
static const long WfsBaud = 9600;
//-------------------------------------------------------------------------
#define  lgs  Serial
static const long LGSBaud = 9600;
//-------------------------------------------------------------------------
void setup() {
  lgs.begin(LGSBaud); lg(F("Log.Serial.start! = ")); lg(LGSBaud); lgln(F(""));
  gas.begin(GasBaud); lg(F("Gas.Serial.start! = ")); lg(GasBaud); lgln(F(""));
  wfs.begin(WfsBaud); lg(F("Wfs.Serial.start! = ")); lg(WfsBaud); lgln(F(""));
  LCD1602_setup();
  LCD1602_Show(0, 0, F("SYS.Start!"));
  //netJoinAP(F("MMMM"),F("1234567890123"));
  DHT_setup();
  netStart();
}
int n = 0;
void loop() {
  //-------------------------------
  DHT_loop();
  AskHCHO();  smartDelayG(500);
  //-------------------------------
  LCD1602_Clear();  LcdHCHO();
  LCD1602_loop_test();
  //-------------------------------
  n++;
  if (n > 50) {
    n = 0;
    Lewei_Loop();
  }
  smartDelayW(500);
  //-------------------------------
}
void gasLoop() {
  //-------------------------------
  gas.listen();
  while (gas.available()) {
    char c = gas.read();
    HCHOCheck(c);
  }
  //-------------------------------
}
void wfsLoop() {
  //-------------------------------
  wfs.listen();
  while (wfs.available()) {
    char c = wfs.read();
    lgs.write(c);
  }
  //-------------------------------
}
void lgsLoop() {
  //-------------------------------
  while (lgs.available()) {
    char c = lgs.read();
  }
  //-------------------------------
}
static void smartDelayW(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    wfsLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
static void smartDelayG(unsigned long ms)
{
  unsigned long start = millis(); do {
    //------------------------------------------
    gasLoop();
    lgsLoop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


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
//LiquidCrystal lcd(7, 8, 9, 5, 4, 3, 2);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);
String t1 = "";
String t2 = "";
String t3 = "";
int n = 0;

void setup() {
  lcd.begin(16, 2);//columns rows
  lcd.print("LCD start...!");
  Serial.begin(115200);
}
void loop() {
  //lcd.clear();
  lcd.setCursor(0, 1);
  n++;
  lcd.print(n);
  delay(1000);
}

void lcd_show_t() {
  lcd.clear();
  t2.trim();
  lcd.setCursor(0, 0);
  lcd.print(t2);
  n = t2.length();
  if (n > 16) {
    t3 = t2.substring(16, n);
    lcd.setCursor(0, 1);
    lcd.print(t3);
  }
}
