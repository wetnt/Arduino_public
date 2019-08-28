/**
   This example
*/
#include <M5StickC.h>
#include <Arduino.h>

void lcd_show(String str) {
  Serial.println(str);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.println(str);
}

void setup()
{
  M5.begin();
  Serial.begin(115200);
  
  //--------------------------------------------------
  M5.Lcd.setRotation(3);
  M5.Axp.ScreenBreath(10);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 2);  
  M5.Lcd.println("M5StickC LCD TEST");
  //--------------------------------------------------
  pinMode(M5_BUTTON_HOME, INPUT);
  //--------------------------------------------------
  BMM150_setup();
}

void loop()
{

  BMM150_loop();
  BMM150_North_Line();
  delay(250);

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
