//-----------------------------------------------------------------
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
//-----------------------------------------------------------------
#include <LCD5110_Graph.h>
LCD5110 myGLCD(3,4,5,6,7);
//-----------------------------------------------------------------
extern uint8_t SmallFont[];
extern uint8_t arduino_logo[];
extern unsigned char TinyFont[];
extern uint8_t The_End[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];
//-----------------------------------------------------------------



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


//-----------------------------------------------------------------
static unsigned char second,minute,hour;
unsigned long t = millis(); 
//-----------------------------------------------------------------

void setup() 
{
  //-----------------------------------------------------------------
  myGLCD.InitLCD(50);
  myGLCD.setFont(SmallFont);
  //-----------------------------------------------------------------
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(500); 
  //-----------------------------------------------------------------
  GpsInt(TimeZone,&mySerial);  
  Serial.println("GPS Read Start!");
  //-----------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.print("GPS Read Start", CENTER, 14); 
  myGLCD.setFont(TinyFont);
  myGLCD.print("(C)2013 by", CENTER, 36);
  myGLCD.print("BOBOKing", CENTER, 42);
  myGLCD.update();
  //-----------------------------------------------------------------
}

void loop() 
{
  //-----------------------------------------------------------------
  GpsRead();  
  //-----------------------------------------------------------------
  LoopTime++;
  if(LoopTime>100000){ 
    //GpsShow();
    GpsLCDShow();
    LoopTime=0;
  }
  //-----------------------------------------------------------------
}

void GpsLCDShow(){
  //-----------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //-----------------------------------------------------------------
  String tdate = String(
  myGps.key + String(" 20") +String(myGps.YY,DEC) + "/" + 
    String(myGps.MT,DEC) + "/" + 
    String(myGps.DD,DEC) 
    );
  String ttime = String(
  String("  ") +
    String(myGps.HH,DEC) + ":" + 
    String(myGps.MM,DEC) + ":" + 
    String(myGps.SC,DEC)
    );
  //String gpsky = String(  myGps.key + " ");

  char str[10];
  dtostrf(myGps.lat,3,5,str);  
  String mylat = str;   
  dtostrf(myGps.lon,3,5,str); 
  String mylon = str;
  dtostrf(myGps.vel,4,2,str);  
  String tv =  str;
  dtostrf(myGps.age,3,0,str);  
  String tf = tv + String(" ") + str;

  myGLCD.print(tdate, 0, 0);
  myGLCD.print(ttime, 0, 9);
  myGLCD.print(mylat, 0, 18);
  myGLCD.print(mylon, 0, 27);
  myGLCD.print(tf, 0, 36);
  //myGLCD.print(tf, 0, 45);
  //-----------------------------------------------------------------
  myGLCD.update();
  //-----------------------------------------------------------------
}

void GpsShow()
{
  //-----------------------------------------------------------------
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
  //-----------------------------------------------------------------
  Serial.print(myGps.key); 
  Serial.print(" ");
  //-----------------------------------------------------------------
  Serial.print(myGps.lat,5); 
  Serial.print(","); 
  Serial.print(myGps.lon,5); 
  Serial.print(" ");
  //-----------------------------------------------------------------
  Serial.print(myGps.vel); 
  Serial.print(",");
  Serial.print(myGps.age); 
  Serial.println();
  //-----------------------------------------------------------------
}





