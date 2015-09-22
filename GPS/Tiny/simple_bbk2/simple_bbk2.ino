#include <SoftwareSerial.h>
#include <TinyGPS.h>
//-------------------------------------------------------------------------
#include <LCD5110_Graph.h>
LCD5110 myGLCD(3,4,5,6,7);
//-------------------------------------------------------------------------
extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
TinyGPS gps;
SoftwareSerial	GpsSerial(10, 11); // RX, TX
//-------------------------------------------------------------------------
static bool feedgps();
static void TinyGpsShow();
//-------------------------------------------------------------------------

void setup() 
{
  //-------------------------------------------------------------------------
  myGLCD.InitLCD(50);
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("GPS Read Start", CENTER, 14); 
  myGLCD.setFont(TinyFont);
  myGLCD.print("(C)2013 by", CENTER, 36);
  myGLCD.print("BOBOKing.COM", CENTER, 42);
  myGLCD.update();
  //-------------------------------------------------------------------------
  delay(500); 
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("HardwareSerial", CENTER, 10); 
  myGLCD.print("Read Start", CENTER, 24); 
  myGLCD.update();
  delay(500); 
  //-------------------------------------------------------------------------
  Serial.begin(115200);
  GpsSerial.begin(9600);
  //-------------------------------------------------------------------------
  TinyGpsShow();
  //-------------------------------------------------------------------------
}
//-------------------------------------------------------------------------
unsigned long NoowTime = 0;
unsigned long ShowTime = 0;
int ShowTimeKey = 1000;//5s
//-------------------------------------------------------------------------
void loop() 
{
  //-------------------------------------------------------------------------
  NoowTime = millis();
  //-------------------------------------------------------------------------
  feedgps();
  //-------------------------------------------------------------------------
  if( NoowTime - ShowTime > ShowTimeKey){ 
    ShowTime = NoowTime;
    //-------------------------------------------------------------------------
    GpsValueRun();
    GpsLCDShow();
    SerialShow();
    //-------------------------------------------------------------------------
  }
  //-------------------------------------------------------------------------
}


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long age;  
float flat, flon;
char sz[32];
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void GpsValueRun(){
  //-------------------------------------------------------------------------
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  sprintf(sz,"%02d/%02d/%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
  sprintf(sz,"%02d/%02d %02d:%02d:%02d",month,day,hour,minute,second);
  gps.f_get_position(&flat, &flon, &age);
  //-------------------------------------------------------------------------
}

void SerialShow(){
  //---------------------------------------------------
  Serial.println("----");
  Serial.println(sz);  
  //Serial.print("age = ");
  //Serial.print(age);
  //Serial.print(" ");
  //---------------------------------------------------
  //Serial.println(age);  
  //Serial.println(flat);
  //Serial.println(flon);
  //---------------------------------------------------
  //Serial.print("sat = ");
  //Serial.print(gps.satellites());
  //Serial.print(" ");
  //Serial.println(gps.hdop());
  //---------------------------------------------------
  //Serial.print("alt = ");
  //Serial.println(gps.f_altitude());
  //Serial.print("spd = ");
  //Serial.println(gps.f_speed_kmph());
  //Serial.print("fan = ");
  //Serial.println(gps.f_course());  
  //---------------------------------------------------
  //float distance = TinyGPS::distance_between(flat, flon, 39.977, 116.332) / 1000;
  //Serial.println(distance);
  //---------------------------------------------------
}

char str[20];
void GpsLCDShow(){
  //-------------------------------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //-------------------------------------------------------------------------
  myGLCD.print(sz, 0,  0);
  //------------------------------------------------
  myGLCD.print("W",  0,  9);  
  dtostrf(flat,3,6,str);
  myGLCD.print(str, 18,  9);
  myGLCD.print("J",  0, 18);  
  dtostrf(flon,3,6,str);
  myGLCD.print(str, 12, 18);
  ////------------------------------------------------
  //myGLCD.print(myGPS.cLock, 0, 27);  
  //myGLCD.print(myGPS.cType, 8, 27);  
  //myGLCD.print("-", 16, 27);    
  //myGLCD.print(myGPS.sGpsn, 24, 27);     
  //myGLCD.print("R", 46, 27); 
  //myGLCD.print(myGPS.sRads, 54, 27);   
  ////------------------------------------------------
  //myGLCD.print("S",  0, 36); 
  //myGLCD.print(myGPS.sSped,  8, 36); 
  //myGLCD.print("F",  46, 36); 
  //myGLCD.print(myGPS.sFans, 54, 36);
  //-------------------------------------------------------------------------
  //myGLCD.print(myGPS.charGPRMC,  0, 36);  
  //-------------------------------------------------------------------------
  myGLCD.update();
  //-------------------------------------------------------------------------
}


static bool feedgps()
{
  while (GpsSerial.available())
  {
    if (gps.encode(GpsSerial.read()))
      return true;
  }
  return false;
}

static void TinyGpsShow()
{
  //-------------------------------------------------------------------------
  Serial.print("Testing TinyGPS library v. "); 
  Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
  Serial.print("Sizeof(gpsobject) = "); 
  Serial.println(sizeof(TinyGPS));
  Serial.println();
  Serial.println("Sats HDOP Latitude Longitude Fix  Date       Time       Date Alt     Course Speed Card  Distance Course Card  Chars Sentences Checksum");
  Serial.println("          (deg)    (deg)     Age                        Age  (m)     --- from GPS ----  ---- to London  ----  RX    RX        Fail");
  Serial.println("--------------------------------------------------------------------------------------------------------------------------------------");
  //-------------------------------------------------------------------------
}

