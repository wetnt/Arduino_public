#include <TinyGPS++.h>
TinyGPSPlus gps;

void TinyGPS_feed(char c) {
  gps.encode(c);
  if (gps.time.isUpdated()) {
    zWork();
  }
}
