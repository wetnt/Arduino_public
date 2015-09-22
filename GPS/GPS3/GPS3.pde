#include <NewSoftSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
NewSoftSerial nss(2, 3);

void gpsdump(TinyGPS &gps);
bool feedgps();

void setup()
{
  Serial.begin(9600);
  nss.begin(9600);
  delay(1000);  
}

void loop()
{
  if (feedgps())
  {
    gpsdump(gps);
  }
}

void gpsdump(TinyGPS &gps)
{
  float flat, flon;
  unsigned long age;
  int year;
  byte month, day, hour, minute, second, hundredths;
  
  gps.f_get_position(&flat, &flon, &age);
  feedgps();
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  feedgps();
  
  Serial.print(year); 
  Serial.print("."); 
  Serial.print(static_cast<int>(month)); 
  Serial.print("."); 
  Serial.print(static_cast<int>(day)); 
  Serial.print("--");      
  Serial.print(static_cast<int>(hour)); 
  Serial.print(":"); 
  Serial.print(static_cast<int>(minute)); 
  Serial.print(":"); 
  Serial.print(static_cast<int>(second)); 
  Serial.print("."); 
  Serial.print(static_cast<int>(hundredths));
  Serial.println();  
  
  Serial.print(flat*100000);
  Serial.print(", ");
  Serial.print(flon*100000);
  Serial.print(", ");
  feedgps();
  Serial.print(gps.f_altitude()); 
  Serial.print(", ");
  feedgps();
  Serial.print(gps.f_speed_kmph());
  Serial.print(", ");
  feedgps();
  Serial.print(gps.course());  
  Serial.println(); 
}
  
bool feedgps()
{
  while (nss.available())
  {
    if (gps.encode(nss.read()))
      return true;
  }
  return false;
}
