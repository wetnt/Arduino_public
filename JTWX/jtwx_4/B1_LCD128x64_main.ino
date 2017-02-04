/*
  LCD  Arduino
  PIN1 = GND
  PIN2 = 5V
  RS(CS) = 8;
  RW(SID)= 9;
  EN(CLK) = 3;
  PIN15 PSB = GND;
*/
#include "LCD12864RSPI.h"
#define AR_SIZE(a) sizeof(a) / sizeof(a[0])

unsigned char bbk_wwws[] = "www.commsat.com";
unsigned char bbk_jtwx[] = {0xBE, 0xC5, 0xCC, 0xEC, 0xCE, 0xA2, 0xD0, 0xC7}; //九天微星
//unsigned char bbk_wj[] = {0xCE, 0xB3, 0xBE, 0xAD, 0xA3, 0xBA}; //纬经
//unsigned char bbk_zt[] = {0xD7, 0xCB, 0xCC, 0xAC, 0xA3, 0xBA}; //姿态
//unsigned char bbk_ws[] = {0xCE, 0xC2, 0xCA, 0xAA, 0xA3, 0xBA}; //温湿

unsigned char bbk_wj[] = {0xCE, 0xB3, 0xBE, 0xAD}; //纬经
unsigned char bbk_zt[] = {0xD7, 0xCB, 0xCC, 0xAC}; //姿态
unsigned char bbk_ws[] = {0xCE, 0xC2, 0xCA, 0xAA}; //温湿

void LCD_128x64_setup() {
  LCDA.Initialise(38, 40, 42); // 屏幕初始化
  delay(100);
}

void LCD_128x64_loop() {
  //------------------------------------------------
  unsigned char wjs[] = " 3997,11632";
  unsigned char zts[] = "128 111 100";
  unsigned char wsd[] = " 39.5C H16%";
  //------------------------------------------------  
  String temperature_str = temperature < 10 ? String(" ") + String((int)temperature) : String((int)temperature);
  String humidity_str = humidity < 10 ? String(" ") + String((int)humidity) : String((int)humidity);
  wsd_str = String("  ") + temperature_str +  String("C  H") + humidity_str + String("%");
  wsd_str.getBytes(wsd, sizeof(wsd));
  //------------------------------------------------
  //------------------------------------------------
  //------------------------------------------------
  //------------------------------------------------
  //LCDA.CLEAR();//清屏
  smartDelay(50); LCDA.DisplayString(0, 2, bbk_jtwx, AR_SIZE(bbk_jtwx)); //第一行第三格开始
  //LCDA.DisplayString(1, 0, bbk_wwws, AR_SIZE(bbk_wwws)); //第二行第一格开始
  smartDelay(50); LCDA.DisplayString(1, 0, bbk_wj, AR_SIZE(bbk_wj)); LCDA.DisplayString(1, 2, wjs, AR_SIZE(wjs));
  smartDelay(50); LCDA.DisplayString(2, 0, bbk_zt, AR_SIZE(bbk_zt)); LCDA.DisplayString(2, 2, zts, AR_SIZE(zts));
  smartDelay(50); LCDA.DisplayString(3, 0, bbk_ws, AR_SIZE(bbk_ws)); LCDA.DisplayString(3, 2, wsd, AR_SIZE(wsd));
  //------------------------------------------------
  //smartDelay(2000);LCDA.CLEAR();//清屏
  //smartDelay(10);  LCDA.DrawFullScreen(logo0);
  smartDelay(1000);
  //------------------------------------------------
}
