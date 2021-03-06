//DS3231
//Date and time functions using DS3231 RTC connected via I2C and Wire lib
//=======================================================
#include <Wire.h>
#include "Sodaq_DS3231.h"
//=======================================================
DateTime now;
DateTime dt(2016,1,31,11,8,0,0);
float rtcTemperature;
char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
//=======================================================
uint32_t old_ts;
//=======================================================
void setup ()
{
  //------------------------------------------------
  lgsetup("DS3231 Basic ...");
  //------------------------------------------------
  Wire.begin();
  rtc.begin();
  //rtc.setDateTime(dt);
  //------------------------------------------------
}

void loop ()
{
  //------------------------------------------------
  rtc.convertTemperature(); rtcTemperature = rtc.getTemperature();
  //------------------------------------------------
  now = rtc.now();
  //------------------------------------------------
  uint32_t ts = now.getEpoch();
  if (old_ts == 0 || old_ts != ts) {
    old_ts = ts;
    //------------------------------------------------
    Serial.print(now.year(), DEC);    lg('/');
    Serial.print(now.month(), DEC);   lg('/');
    Serial.print(now.date(), DEC);    lg('/');
    Serial.print(now.hour(), DEC);    lg(':');
    Serial.print(now.minute(), DEC);  lg(':');
    Serial.print(now.second(), DEC);  lg('\t');
    //------------------------------------------------
    Serial.print(weekDay[now.dayOfWeek()]); lg("\t");
    //------------------------------------------------
    //Serial.print("Seconds since Unix Epoch: "); Serial.print(ts, DEC);lg("\t");
    //------------------------------------------------
    lg(rtcTemperature);Serial.print(" deg C"); lg();
    //------------------------------------------------
  }
  //------------------------------------------------
  delay(1000);
  //------------------------------------------------
}
