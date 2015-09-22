//-----------------------------------------------------------------
int TimeZone = 8;
//-----------------------------------------------------------------
class GPS{
public:
  int TimeZone;
  int YY,MT,DD,HH,MM,SC,MS;
  char key;
  float lat,lon,hit,vel,age;
};
//-----------------------------------------------------------------
GPS myGps;
//-----------------------------------------------------------------
long LoopTime;
long LoopTimeX;
int ledState = 0;
//-----------------------------------------------------------------

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

//-----------------------------------------------------------------
static unsigned char second,minute,hour;
unsigned long t = millis(); 
//-----------------------------------------------------------------

void setup() 
{
  //-----------------------------------------------------------------
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(500); 
  GpsInt(TimeZone,&mySerial);
  Serial.println("GPS Read Start!");
  //-----------------------------------------------------------------
}

void loop() 
{
  //-----------------------------------------------------------------
  GpsRead();  
  //-----------------------------------------------------------------
  LoopTime++;
  if(LoopTime>150000){ 
    GpsShow();
    LoopTime=0;
  }
  //-----------------------------------------------------------------
}


void GpsShow()
{	
  Serial.print(myGps.YY); 
  Serial.print("/");
  Serial.print(myGps.MT); 
  Serial.print("/");
  Serial.print(myGps.DD); 
  Serial.print(" ");
  Serial.print(myGps.HH); 
  Serial.print(":");
  Serial.print(myGps.MM); 
  Serial.print(":");
  Serial.print(myGps.SC); 
  Serial.print(".");
  Serial.print(myGps.MS); 
  Serial.print(" ");

  Serial.print(myGps.key); 
  Serial.print(" ");

  Serial.print(myGps.lat,5); 
  Serial.print(","); 
  Serial.print(myGps.lon,5); 
  Serial.print(" ");

  Serial.print(myGps.vel); 
  Serial.print(",");
  Serial.print(myGps.age); 
  Serial.println();
}

