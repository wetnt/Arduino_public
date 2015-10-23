#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(3, 4);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);

  Serial.print("Simple TinyGPS library v. ");
  Serial.println(TinyGPS::library_version());
  Serial.println();
}

void loop()
{
  boolean newData = false;

  while (ss.available())
  {
    char c = ss.read();
    if (gps.encode(c))
      newData = true;
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    int Year;
    byte Month, Day, Hour, Minute, Second;
    gps.f_get_position(&flat, &flon, &age);
    gps.crack_datetime(&Year, &Month, &Day, &Hour, &Minute, &Second, NULL, &age);

    Serial.print(Year);
    Serial.print("-");
    Serial.print(Month);
    Serial.print("-");
    Serial.print(Day);
    Serial.print(" ");
    Serial.print(Hour);
    printDigits(Minute);
    printDigits(Second);

    Serial.print(" ");
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 7);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 7);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());

    Serial.print(" ");
    Serial.print(age);

    Serial.println();

  }

}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
