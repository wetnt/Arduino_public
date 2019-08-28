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
int lcd_Breath = 8;//(7+16)/2;
//--------------------------------------------------
void setup() {
  //--------------------------------------------------
  lgsetup("M5StickC......LEWEI") ;
  lgln("-----------------------------------");
  //--------------------------------------------------
  M5.begin(); lcd_setup(); 
  //--------------------------------------------------
  Wire.begin(0, 26); wifi_setup(); 
  pinMode(M5_BUTTON_HOME, INPUT);
  //--------------------------------------------------
  Battery_setup(); smartDelay(200);
  BMM150_setup(); smartDelay(200);
  DHT12_setup();  smartDelay(200);
  BMP280_setup(); smartDelay(200);
  //--------------------------------------------------
  WIFI_Lewei_Report();
  //--------------------------------------------------
  tLoop_Setup();
  //--------------------------------------------------
}
void loop() {
  if (ts_loop(1)) {
    DHT12_loop();
    BMP280_loop();
    BMM150_loop();
    WIFI_TIME_SHOW();
    dt.addTimeSecond();
  }
  if (ts_loop(30)) {
    M5.Lcd.fillScreen(BLACK); WIFI_TIME_SHOW();
    WIFI_Lewei_Report();
    Battery_loop();
  }

  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    
    lcd_Breath+=8;
    if(lcd_Breath>16)lcd_Breath=8;
    M5.Axp.ScreenBreath(lcd_Breath);
    
    M5.Lcd.fillScreen(BLACK); WIFI_TIME_SHOW();
    WIFI_Lewei_Report();
  }

  if (digitalRead(M5_BUTTON_RST) == LOW) {
    M5.Axp.LightSleep(SLEEP_SEC(2));
    delay(6);
    M5.Axp.DeepSleep(SLEEP_SEC(2));
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
