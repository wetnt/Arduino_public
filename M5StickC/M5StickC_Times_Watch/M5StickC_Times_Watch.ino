//--------------------------------------------------
//https://docs.m5stack.com/#/zh_CN/api
//--------------------------------------------------
#include <M5StickC.h>
#include <Wire.h>
//--------------------------------------------------
#include "BBK_TIME.h"
//--------------------------------------------------
void setup() {
  //--------------------------------------------------
  lgsetup("M5StickC......Times") ;
  lgln("-----------------------------------");
  //--------------------------------------------------
  M5.begin(); lcd_setup();
  //--------------------------------------------------
  Wire.begin(0, 26);
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
  //--------------------------------------------------
  //pinMode(M5_LED, OUTPUT);
  //digitalWrite(M5_LED, HIGH);
  //--------------------------------------------------
  Battery_setup(); smartDelay(200);
  //--------------------------------------------------
  tLoop_Setup();
  M5.Lcd.fillScreen(BLACK);
  //--------------------------------------------------
}
void loop() {
  if (ts_loop(1)) {
    Battery_loop(); Battery_Serial();
    WIFI_TIME_SHOW();
    dt.addTimeSecond();
  }
  if (ts_loop(30)) {
  }

  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    delay(200);
    M5.Lcd.fillScreen(BLACK);
    TimeShowKey_turn();
  }

  if (digitalRead(M5_BUTTON_RST) == LOW) {
    delay(200);
    M5.Lcd.fillScreen(BLACK);
    lcd_Breath_set();
  }
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    //lgFeed(); wfs_loop(); Dog_Loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
