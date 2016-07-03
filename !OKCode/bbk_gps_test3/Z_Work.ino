void zWork() {
  char tms[20];
  sprintf(tms, "$LF,%04d%02d%02d,%02d%02d%02d", gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second()); lg(tms);   sd(tms);
  lg(','); lg(gps.location.isValid()); lg(','); lg(gps.satellites.value()); lg(','); lg(gps.hdop.value()); lg(','); lg(gps.location.lat(), 7); lg(','); lg(gps.location.lng(), 7); lg(','); lg((int)gps.altitude.meters());
  sd(','); sd(gps.location.isValid());
  sd(','); sd(gps.satellites.value());
  sd(','); sd(gps.hdop.value());
  sd(','); sd(gps.location.lat(), 7);
  sd(','); sd(gps.location.lng(), 7);
  sd(','); sd((int)gps.altitude.meters());

  lg(','); lg((int)imu.roll); lg(','); lg((int)imu.pitch); lg(','); lg((int)imu.yaw);
  sd(','); sd((int)imu.roll); sd(','); sd((int)imu.pitch); sd(','); sd((int)imu.yaw);
  lg(";"); lg();
  sd(";"); sd();
}

