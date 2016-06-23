#include <TinyGPS++.h>
TinyGPSPlus gps;

void TinyGPS_feed(char c) {
  gps.encode(c);
  if (gps.time.isUpdated()) {
    char sz[20];
    sprintf(sz, "$LF,%04d%02d%02d,%02d%02d%02d", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second()); 
    //lg(sz);lg(','); lg(gps.location.isValid()); lg(','); lg(gps.satellites.value()); lg(','); lg(gps.hdop.value());lg(',');lg(gps.location.lat(), 7); lg(','); lg(gps.location.lng(), 7); lg(','); lg(gps.altitude.meters()); lg(";");lg();
    sd(sz);sd(','); sd(gps.location.isValid()); sd(','); sd(gps.satellites.value()); sd(','); sd(gps.hdop.value());sd(',');sd(gps.location.lat(), 7); sd(','); sd(gps.location.lng(), 7); sd(','); sd(gps.altitude.meters()); sd(";");sd();    
  }
}
