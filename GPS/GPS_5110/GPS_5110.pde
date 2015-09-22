//-----------------------------------------------------------------
#include "PCD8544.h"
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// 3 pin LCD control, SCLK, DN, D/C (CS, RST)
//PCD8544(SCLK,DIN,D/C,CS,RST)
//PCD8544 nokia = PCD8544(7, 6, 5, 4, 3);
//#define LOGO16_GLCD_HEIGHT 16 
//#define LOGO16_GLCD_WIDTH  16 
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
  //------------------------
  Serial.begin(9600);
  pinMode(13, OUTPUT);      
  //------------------------
  GpsInt(TimeZone);
  Serial.print("fghsdhfdgfh"); 
  //GpsShow();
  //------------------------
//  nokia.init();
//  nokia.setContrast(40);
//  nokia.clear();
  //------------------------
//  nokia.setPixel(10, 10, BLACK);// draw a single pixel
//  nokia.setCursor(0, 17);
  //------------------------
}

void loop() 
{
  GpsRead();
  LoopTime++;
  if(LoopTime>400){ 
    GpsShow();
    //NokiaShow();
    LoopTime=0;
  } 
}


void NokiaShow()
{
//  nokia.clear();
//  nokia.setCursor(0, 0);
//  nokia.print(myGps.YY,DEC);
//  nokia.println("/");
//  nokia.print(myGps.MT,DEC);
//  nokia.println("/");
//  nokia.print(myGps.DD,DEC);
//  nokia.println(" ");
//
//  nokia.setCursor(2, 0);
//  nokia.print(myGps.HH);
//  nokia.println(":");
//  nokia.print(myGps.MM);
//  nokia.println(":");
//  nokia.print(myGps.SS);
//  nokia.println(".");  
//  nokia.print(myGps.MS);
//  nokia.println(" ");

//  nokia.display();
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

  if( myGps.key == 'A' ){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}

