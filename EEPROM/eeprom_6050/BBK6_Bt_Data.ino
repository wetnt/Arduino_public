struct MyBtType {
  long Times;
  char Types;
  int Level;
  int Temps;
  //char name[10];
};

void test_save_MyBtType() {
  int ad;
  MyBtType c1 = {3.14l, 'r', 100, 0};
  MyBtType c2 = {3.15l, 's', 200, 0};
  ad = address;     EEPROM.put( ad, c1 );
  ad = sizeof(c1);  EEPROM.put( ad, c2 );
}

void test_read_MyBtType() {
  MyBtType c1, c2; int ad;
  ad = address;     EEPROM.get( ad, c1 );
  ad = sizeof(c1);  EEPROM.get( ad, c2 );

  lg( "Read custom object from EEPROM: " );
  lg( c1.Times ); lg(' ');
  lg( c1.Types ); lg(' ');
  lg( c1.Level ); lg(' ');
  lg( c1.Temps ); lg();

  lg( "Read custom object from EEPROM: " );
  lg( c2.Times ); lg(' ');
  lg( c2.Types ); lg(' ');
  lg( c2.Level ); lg(' ');
  lg( c2.Temps ); lg();
}
