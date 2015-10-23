#include <TinyGPS.h>       // http://arduiniana.org/libraries/TinyGPS/
TinyGPS gps;
const int offset = 1;

void setup()
{
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  Serial.println("Waiting for GPS time ... ");
}

void loop()
{
  while (Serial.available()) {
    if (gps.encode(Serial.read())) { // process gps messages
      unsigned long age;
      int Year;
      byte Month, Day, Hour, Minute, Second;
      gps.crack_datetime(&Year, &Month, &Day, &Hour, &Minute, &Second, NULL, &age);
      if (age < 500) {
      }
      Serial.print(Year);
    }
  }
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

