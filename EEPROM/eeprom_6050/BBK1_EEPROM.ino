#include <EEPROM.h>
//------------------------------------------------
//- Arduno Duemilanove: 512b EEPROM storage.
//- Arduino Uno:        1kb EEPROM storage.
//- Arduino Mega:       4kb EEPROM storage.
//------------------------------------------------
int address = 0;
int add_start = 0, add_step = 1;
void rom_setup(int _add_start, int _add_step) {
  add_start = _add_start; address = _add_start;
  add_step = _add_step;
}
void rom_loop() {
  test_read();
}
void rom_clear(){
    for ( int i = 0 ; i < EEPROM.length() ; i++ )
    EEPROM.write(i, 0);
}

void test_update() {
  int val = analogRead(0) / 4;
  EEPROM.update(address, val);
  lg(address); lg("="); lg(val); lg();
  //EEPROM.read(address);
  //EEPROM.write(address, val);
  address = address + 4;
  if (address == EEPROM.length()) {
    address = 0;
    lgln("loop_stop");
    for (;;);
  }
  delay(100);
}
void test_read() {
  //--------------------------------------
  int val = EEPROM.read(address);
  lg(address); lg("="); lg(val); lg();
  address = address + 1;
  //--------------------------------------
  if (address >= EEPROM.length()) {
    lgln("loop_stop");
    address = 0;
    for (;;);
  }
  //--------------------------------------
  delay(10);
  //--------------------------------------
}
