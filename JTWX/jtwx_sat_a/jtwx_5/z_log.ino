void logshow() {
  lg(wsd_str); lg(',');
  float voltage = s3.vSum * (5.0 / 1023.0);
  lg(voltage); lg('v');lg(',');
  IMU_show();
  lg();
}
