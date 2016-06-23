#include <TinyGPS++.h>
TinyGPSPlus gps;

//void printDateTime(TinyGPSDate &d, TinyGPSTime &t) {
//  if (d.isValid()) {
//    char sz[32];
//    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
//    lg(sz);
//  }
//  if (t.isValid()) {
//    char sz[32];
//    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
//    Serial.print(sz);
//  }
//  lg(" "); lg("age=");  lg(d.age(), 5, 5);
//}


void TinyGPS_feed(char c) {
  if (gps.encode(c)) {
    //lg(); lg("-------------------------------------------------");lg();

    lt(); lgDigits(gps.date.year()); lgDigits(gps.date.month()); lgDigits(gps.date.day());
    lt(); lgDigits(gps.time.hour()); lgDigits(gps.time.minute()); lgDigits(gps.time.second());

    lt(); lg("loc=");  lg(gps.location.isValid());
    lt(); lg("sat=");  lg(gps.satellites.value());
    lt(); lg("hdop=");  lg(gps.hdop.value());

    lt(); lg("LAT=");  lg(gps.location.lat(), 7);
    lt(); lg("LON=");  lg(gps.location.lng(), 7);

    lt(); lg("alt=");  lg(gps.altitude.meters());
    lt(); lg("cor=");  lg(gps.course.deg());
    lt(); lg("spd=");  lg(gps.speed.kmph());

    //lt(); lg("age=");  lg(gps.location.age());
    //lt(); lgDigits(gps.date.age());

    // printDateTime(gps.date, gps.time); lg();
    lt(); lg(TinyGPSPlus::cardinal(gps.course.value())); lg();


    char sz[12];
    sprintf(sz, "%04d/%02d/%02d %02d:%02d:%02d,", d.year(), d.month(), d.day(), t.hour(), t.minute(), t.second()); lg(sz); ss_send(sz);
    
    //lg(gps.location.isValid());
    //ss.print(gps.location.lat(), 7); lg(","); ss.print(gps.location.lng(), 7);lg(","); lg(gps.altitude.meters());lg(",");lg(gps.speed.kmph()); lg(","); lg(","); 

  }
}
