void logshow() {
  lg(wsd_str); lg(',');
  float voltage = s3.vSum * (5.0 / 1023.0);
  lg(voltage); lg('v');lg(',');

  lg(accx); lg(',');
  lg(accy); lg(',');
  lg(accz); lg(',');
  lg(gyrox); lg(',');
  lg(gyroy); lg(',');
  lg(gyroz); lg(',');

  lg();
}
