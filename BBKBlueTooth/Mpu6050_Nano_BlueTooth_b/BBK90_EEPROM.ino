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
