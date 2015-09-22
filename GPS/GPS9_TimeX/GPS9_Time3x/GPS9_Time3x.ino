//-----------------------------------------------------------------
#include <dht.h>
dht DHT;
#define DHT11_PIN 7
//-----------------------------------------------------------------

//-----------------------------------------------------------------
int TimeZone = 8;
//-----------------------------------------------------------------
class GPS{
public:
  int TimeZone;
  int YY,MT,DD,HH,MM,SK,MS;
  char key;
  float lat,lon,hit,vel,age;
};
//-----------------------------------------------------------------
GPS myGps;
//-----------------------------------------------------------------
unsigned long LoopTime;
unsigned long LoopTimeX;
unsigned int ledState = 0;
unsigned long t = millis(); 
//-----------------------------------------------------------------


//-----------------------------------------------------------------
const int dataPin = 2; // SER - DIO //DATA
const int latchPin = 3;// RCK //ST_CP 低電位鎖定資料並輸出Q0~Q7;高電位更新 
const int clockPin = 4;// SCK //SH_CP 

unsigned char fseg[]={
  0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf};
unsigned char segbit[]={
  0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char disbuf[8]={
  0,0,0,0,0,0,0,0};
//-----------------------------------------------------------------

void TubeShow()
{

  for (int j = 0; j < 8; j++)
  {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, segbit[j]);
    shiftOut(dataPin, clockPin, MSBFIRST, fseg[disbuf[j]]);
    digitalWrite(latchPin, 1);
    delay(1);
  }

}

void TubeSetTime()
{
  disbuf[0]=myGps.SK%10;
  disbuf[1]=myGps.SK/10;
  disbuf[2]=10;
  disbuf[3]=myGps.MM%10;
  disbuf[4]=myGps.MM/10;
  disbuf[5]=10;
  disbuf[6]=myGps.HH%10;
  disbuf[7]=myGps.HH/10;  
}

void TubeSetDate()
{
  disbuf[0]=myGps.DD%10;
  disbuf[1]=myGps.DD/10;
  disbuf[2]=myGps.MT%10;
  disbuf[3]=myGps.MT/10;
  disbuf[4]=myGps.YY%10;
  disbuf[5]=myGps.YY/10;  
  disbuf[6]=0;
  disbuf[7]=2;  
}		


void TubeSetDht()
{
  int chk = DHT.read11(DHT11_PIN);

  disbuf[0]=10;
  disbuf[1]=(int)DHT.humidity*10%10;
  disbuf[2]=(int)DHT.humidity%10;
  disbuf[3]=(int)DHT.humidity/10;
  disbuf[4]=10;
  disbuf[5]=(int)DHT.temperature*10%10;
  disbuf[6]=(int)DHT.temperature%10;
  disbuf[7]=(int)DHT.temperature/10;  
}		

void setup() 
{
  //-----------------------------------------------------------------
  Serial.begin(9600);
  delay(200); 
  GpsInt(TimeZone);
  //-----------------------------------------------------------------
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  //-----------------------------------------------------------------
}

void loop() 
{
  //-----------------------------------------------------------------
  LoopTimeX++; 
  if(LoopTimeX>100){ 
    TubeShow();     
    LoopTimeX=0;
  }
  //-----------------------------------------------------------------
  GpsRead();
  //-----------------------------------------------------------------
  LoopTime++;
  if(LoopTime>20000){ 
    //GpsShow(); 
    //DhtRead();
    //-----------------------------------------------------------------
    switch (ledState)
    {
    case 0:
      TubeSetDate();
      break; 
    case 1:
      TubeSetTime();
      break; 
    case 2:
      TubeSetDht();
      break;
    }
    ledState++;
    if(ledState>2)
    {
      ledState=0;
    }
    LoopTime=0;
  } 
  //-----------------------------------------------------------------
}

