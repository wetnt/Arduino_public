/**
   This example
*/
#include <M5StickC.h>
#include <Arduino.h>
#include <Wire.h>
// libraries
#include "bmm150.h"
#include "bmm150_defs.h"

BMM150 bmm = BMM150();

void setup()
{
  M5.begin();
  Serial.begin(115200);
  Wire.begin(0, 26);


  //--------------------------------------------------
  M5.Lcd.setRotation(3);
  M5.Axp.ScreenBreath(10);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 2);  
  M5.Lcd.println("M5StickC LCD TEST");
  //--------------------------------------------------
  pinMode(M5_BUTTON_HOME, INPUT);
  //--------------------------------------------------
  

  if (bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
    Serial.println("Chip ID can not read!");
    while (1);
  } else {
    Serial.println("Initialize done!");
  }

  ttt_setup();
}

void loop()
{

  ttt_loop();

  //  bmm150_mag_data value;
  //  bmm.read_mag_data();
  //
  //  value.x = bmm.raw_mag_data.raw_datax;
  //  value.y = bmm.raw_mag_data.raw_datay;
  //  value.z = bmm.raw_mag_data.raw_dataz;
  //
  //  float xyHeading = atan2(value.x, value.y);
  //  float zxHeading = atan2(value.z, value.x);
  //  float heading = xyHeading;
  //
  //  if(heading < 0)
  //    heading += 2*PI;
  //  if(heading > 2*PI)
  //    heading -= 2*PI;
  //  float headingDegrees = heading * 180/M_PI;
  //  float xyHeadingDegrees = xyHeading * 180 / M_PI;
  //  float zxHeadingDegrees = zxHeading * 180 / M_PI;
  //
  //  Serial.print("Heading: ");
  //  Serial.println(headingDegrees);
  //
  //  delay(100);
}
