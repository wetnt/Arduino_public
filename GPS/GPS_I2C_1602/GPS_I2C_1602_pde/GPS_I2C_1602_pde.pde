#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);  
// set the LCD address to 0x20 for a 16 chars and 2 line display
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
static unsigned char second,minute,hour;
unsigned long t = millis(); 
//-----------------------------------------------------------------

void setup() 
{  
  //-----------------------------------------------------------------
  lcd.init(); // initialize the lcd 
  lcd.backlight();
  //-----------------------------------------------------------------
  Serial.begin(9600);
  GpsInt(TimeZone);
  //-----------------------------------------------------------------
}

void loop() 
{
  //-----------------------------------------------------------------
  GpsRead();
  //-----------------------------------------------------------------
  LoopTime++;
  if(LoopTime>1000){ 
    GpsShow(); 
    LoopTime=0;
  } 
  //-----------------------------------------------------------------
}


void GpsShow()
{	
  lcd.clear();
//  lcd.print(myGps.YY,DEC);
//  lcd.print("/");
//  lcd.print(myGps.MT,DEC);
//  lcd.print("/");
//  lcd.print(myGps.DD,DEC);
//  lcd.print(" ");
//  lcd.print(myGps.HH,DEC);
//  lcd.print(":");
//  lcd.print(myGps.MM,DEC);
//  lcd.print(":");
//  lcd.print(myGps.SS,DEC);
  
  //lcd.setCursor(0, 1);
//  lcd.print(myGps.key); 
//  lcd.print(" ");

  lcd.print(myGps.lat,4);
  lcd.print(","); 
  //lcd.setCursor(0, 1);
  lcd.print(myGps.lon,4);

//  lcd.print(myGps.vel); 
//  lcd.print(",");
//  lcd.print(myGps.age); 
//  lcd.println();
}



