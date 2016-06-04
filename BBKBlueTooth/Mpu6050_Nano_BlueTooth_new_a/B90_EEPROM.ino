#include <EEPROM.h>
//------------------------------------------------
//- Arduno Duemilanove: 512b EEPROM storage.
//- Arduino Uno:        1kb EEPROM storage.
//- Arduino Mega:       4kb EEPROM storage.
//------------------------------------------------
void rom_clear() {
  for ( int i = 0 ; i < EEPROM.length() ; i++ )
    EEPROM.write(i, 0);
}
//==============================================================================
/*
struct MyBtType {
  long Times;
  //char name[10];
};
void test_save_MyBtType() {
  MyBtType c1 = {3.14l, 'r', 100, 0};
  MyBtType c2 = {3.15l, 's', 200, 0};
  int ad = 0;             EEPROM.put( ad, c1 );
  ad = sizeof(MyBtType);  EEPROM.put( ad, c2 );
}
void test_read_MyBtType() {
  MyBtType c1, c2;
  int ad = 0;       EEPROM.get( ad, c1 ); lg( "c1: " ); c1.show(ad);
  ad = sizeof(c1);  EEPROM.get( ad, c2 ); lg( "c2: " ); c2.show(ad);
}
*/
//==============================================================================
