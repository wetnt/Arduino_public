long LastSendTime = 0;
void zWork() {
  DS18B20_loop(); //DS18B20_print();
  //boolean GpsIsLock = gps.location.isValid();
  char tms[20];
  //sprintf(tms, "$LF,%04d%02d%02d,%02d%02d%02d,", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second()); lg(tms); sd(tms);
  sprintf(tms, "$LF,%02d%02d%02d%02d%02d,", gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second()); lg(tms); sd(tms);
  //lg(','); lg(gps.satellites.value()); lg(','); lg(gps.hdop.value()); lg(',');
  //sd(','); sd(gps.satellites.value()); sd(','); sd(gps.hdop.value()); sd(',');
  lg(gps.location.lat(), 7); lg(','); lg(gps.location.lng(), 7); lg(','); lg((int)gps.altitude.meters());
  sd(gps.location.lat(), 7); sd(','); sd(gps.location.lng(), 7); sd(','); sd((int)gps.altitude.meters());
  lg(','); lg((int)dt[0]);
  sd(','); sd((int)dt[0]);
  lg(";"); lg();
  sd(";"); sd();
  LastSendTime = millis(); Dog_Loop();
}
void zLastCheck() {
  if (millis() - LastSendTime > 10000) zWork();
}

