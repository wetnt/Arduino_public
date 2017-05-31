#include <Arduino.h>
#include <ESP8266WiFi.h>
//---------------------------------------------------------------------------------
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup() {
  Wire.begin(D4,D3); //定义I2C接口，并启动，ESP8266-12E的 2 和 14 口是原本定义为I2C接口，其他模块查看手册，用于读取BMP180的参数
  //--------------------------------------------
  matrix.begin(0x71);
  matrix.setRotation(0);
  matrix.setTextSize(1);
  //--------------------------------------------
  matrix.setTextWrap(false);
  matrix.setTextColor(1);
  //--------------------------------------------
  matrix.clear();
  matrix.setCursor(0, 0);
  matrix.print("ABC");
  matrix.writeDisplay();
  //--------------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:

}
