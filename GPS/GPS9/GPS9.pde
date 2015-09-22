#include <NewSoftSerial.h>
NewSoftSerial nss(2, 3);
int TimeZone = 8;
//-----------------------------------------------------------------
int YY,MT,DD,HH,MM,SS,MS;
char GpsKey='s';
float flatitude=0; 
float flongitud=0;
int velocidad =0;  //速度
int cursoReal =0;  //磁偏角
//-----------------------------------------------------------------

class GPS{
  public:
   int lat;int lng;
};
GPS myGps;


void setup() 
{
  Serial.begin(9600);
  nss.begin(9600);
  delay(1000); 
  GpsInt();
  myGps.lat = 5;
}

void loop() 
{
	GpsRead();
	//GpsShow();	
}


void GpsShow()
{	
	Serial.print(YY); Serial.print("_");
	Serial.print(MT); Serial.print("_");
	Serial.print(DD); Serial.print(" ");
	Serial.print(HH); Serial.print(":");
	Serial.print(MM); Serial.print(":");
	Serial.print(SS); Serial.print(".");
	Serial.print(MS); Serial.print(" ");
	
	Serial.print(GpsKey); Serial.print(" ");

	Serial.print(flatitude); Serial.print(","); 
	Serial.print(flongitud); Serial.print(" ");
	
	Serial.print(velocidad); 
	Serial.print(",");
	Serial.print(cursoReal); 
	Serial.println();
}




