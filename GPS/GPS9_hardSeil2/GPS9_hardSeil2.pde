//-----------------------------------------------------------------
int TimeZone = 8;
//-----------------------------------------------------------------
class GPS{
  public:
    int TimeZone;
    int YY,MT,DD,HH,MM,SS,MS;
    char key;
    float lat,lon,hit,vel,age;
};
//-----------------------------------------------------------------
GPS myGps;
//-----------------------------------------------------------------
long LoopTime;
//-----------------------------------------------------------------


void setup() 
{
  Serial.begin(9600);
  delay(1000); 
  GpsInt(TimeZone);
  Serial.print("/////////////");
}

void loop() 
{
   GpsRead();
   LoopTime++;
   if(LoopTime>400){ 
     GpsShow();
     LoopTime=0;
   } 
}


void GpsShow()
{	
	Serial.print(myGps.YY); Serial.print("/");
	Serial.print(myGps.MT); Serial.print("/");
	Serial.print(myGps.DD); Serial.print(" ");
	Serial.print(myGps.HH); Serial.print(":");
	Serial.print(myGps.MM); Serial.print(":");
	Serial.print(myGps.SS); Serial.print(".");
        Serial.print(myGps.MS); Serial.print(" ");
	
	Serial.print(myGps.key); Serial.print(" ");

	Serial.print(myGps.lat,5); Serial.print(","); 
	Serial.print(myGps.lon,5); Serial.print(" ");
	
	Serial.print(myGps.vel); 
	Serial.print(",");
	Serial.print(myGps.age); 
	Serial.println();
}
