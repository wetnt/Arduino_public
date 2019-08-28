//--------------------------------------------------
//https://docs.m5stack.com/#/zh_CN/api
//--------------------------------------------------
#include <M5StickC.h>
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
//--------------------------------------------------
#include "BBK_TIME.h"
//--------------------------------------------------
void setup() {
  //--------------------------------------------------
  lgsetup("M5StickC......Times") ;
  lgln("-----------------------------------");
  //--------------------------------------------------
  M5.begin(); lcd_setup(); wifi_setup();
  //--------------------------------------------------
  Wire.begin(0, 26);
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
  //--------------------------------------------------
  //pinMode(M5_LED, OUTPUT);
  //digitalWrite(M5_LED, HIGH);
  //--------------------------------------------------
  Battery_setup(); smartDelay(200);
  BMM150_setup(); smartDelay(200);
  DHT12_setup();  smartDelay(200);
  BMP280_setup(); smartDelay(200);
  //--------------------------------------------------
  tLoop_Setup();
  M5.Lcd.fillScreen(BLACK);
  //--------------------------------------------------
  WIFI_Lewei_Report();
  //--------------------------------------------------
}
void loop() {
  if (ts_loop(1)) {
    DHT12_loop();
    BMP280_loop();
    BMM150_loop();
    wifi_loop();
    WIFI_TIME_SHOW();
    Battery_loop(); //Battery_Serial();
    dt.addTimeSecond();
  }
  if (ts_loop(30)) {
    WIFI_Lewei_Report();
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

    //esp_restart();
    //    M5.Axp.LightSleep(SLEEP_SEC(2));
    //    delay(6);
    //    M5.Axp.DeepSleep(SLEEP_SEC(2));
  }

  //smartDelay(20 * 1000);
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
