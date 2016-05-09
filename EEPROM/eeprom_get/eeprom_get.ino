#include <EEPROM.h>
int address = 0;
void setup() {
  Serial.begin( 115200 );
  while (!Serial) {
    ;
  }

  test_save();
  test_read();
}

struct MyObject {
  float field1;
  byte field2;
  char name[10];
};

void test_save() {
  int ad;
  MyObject c1 = {3.14f, 100, "Work_a!"};
  MyObject c2 = {3.15f, 200, "Work_b!"};
  ad = address;     EEPROM.put( ad, c1 );
  ad = sizeof(c1);  EEPROM.put( ad, c2 );
}

void test_read() {
  MyObject c1, c2; int ad;
  ad = address;     EEPROM.get( ad, c1 );
  ad = sizeof(c1);  EEPROM.get( ad, c2 );

  Serial.println( "Read custom object from EEPROM: " );
  Serial.println( c1.field1 );
  Serial.println( c1.field2 );
  Serial.println( c1.name );

  Serial.println( "Read custom object from EEPROM: " );
  Serial.println( c2.field1 );
  Serial.println( c2.field2 );
  Serial.println( c2.name );
}


void loop() {
}
