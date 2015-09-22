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
long LoopTimeX;
int ledState = LOW;
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

static unsigned char second,minute,hour;
unsigned long t = millis(); 
//-----------------------------------------------------------------

void TubeShow() {

  for (int j = 0; j < 8; j++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, segbit[j]);
    shiftOut(dataPin, clockPin, MSBFIRST, fseg[disbuf[j]]);
    digitalWrite(latchPin, 1);
    delay(1);
  }

}

void TubeSetTime()
{
  disbuf[0]=myGps.SS%10;
  disbuf[1]=myGps.SS/10;
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


void setup() 
{
  //-----------------------------------------------------------------
  Serial.begin(9600);
  delay(1000); 
  GpsInt(TimeZone);
  Serial.println("GPS Read Start!");
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
    if (ledState == LOW)
    {
      ledState = HIGH;
      TubeSetTime();
    }
    else{
      ledState = LOW;
      TubeSetDate();
    }
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
  Serial.print(myGps.SS); 
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




