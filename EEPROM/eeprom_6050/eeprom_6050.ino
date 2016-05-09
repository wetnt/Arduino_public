void setup() {
  lgsetup("BBK EEPROM TEST!");
  lgln("loop_stop_start");

  test_save_MyBtType();
  test_read_MyBtType();
}


void loop() {
}
