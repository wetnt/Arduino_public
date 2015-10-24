#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LCD5110_Graph.h>
//-------------------------------------------
SoftwareSerial	GpsSerial(10,13); // RX, TX
SoftwareSerial	mySerial(11,12);
LCD5110 myGLCD(3,4,5,6,7);
TinyGPSPlus gps;
//-------------------------------------------
static bool feedgps();
static void TinyGpsShow();
extern uint8_t SmallFont[];
//-------------------------------------------
String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//-------------------------------------------


//-------------------------------------------------------------------------
int YY,MD,DD,HT,MT,ST;
float WW,JJ,HH,VV,FX;
int SN,SR;
bool KK;
char KT;
String sDate,tDate,sTime;//YMDHMS
String sLats,sLons,sHigh,sSped,sFans;//WJHVF
String cLock,cType,sGpsn,sRads,sSeal;//KK;KT;SN;SR;HZ;
//-------------------------------------------------------------------------
char str[32];
void GpsValueRun(){
  //-------------------------------------------------------------------------
  KK = gps.fixhave;
  //-------------------------------------------------------------------------
  YY = gps.date.year();
  MD = gps.date.month();
  DD = gps.date.day();
  HT = gps.time.hour();
  MT = gps.time.minute();
  ST = gps.time.second();
  HT = HT + 8;
  if( HT > 23 ){
    HT = HT - 24;
    DD = DD + 1;
  }
  //-------------------------------------------------------------------------
  WW = gps.location.lat();
  JJ = gps.location.lng(); 
  //-------------------------------------------------------------------------
  HH = gps.altitude.meters();
  FX = gps.course.deg();
  VV = gps.speed.kmph();
  SN = gps.satellites.value();
  SR = gps.hdop.value();
  //-------------------------------------------------------------------------
  dtostrf(KK,1,0,str);   
  cLock = str;
  dtostrf(KT,2,0,str);   
  cType = str;
  //-------------------------------------------------------------------------
  sDate = String( String(MD,DEC) + "/" + String(DD,DEC) );
  sTime = String( String(HT,DEC) + ":" + String(MT,DEC) + ":" + String(ST,DEC) );
  tDate = String( String(YY,DEC) + "/" + sDate + " " + sTime );
  //-------------------------------------------------------------------------
  dtostrf(WW,3,6,str);  
  sLats = str;
  dtostrf(JJ,3,6,str);  
  sLons = str;
  dtostrf(HH,4,0,str);  
  sHigh = str;
  dtostrf(VV,3,1,str);  
  sSped = str;
  dtostrf(FX,3,1,str);  
  sFans = str;
  dtostrf(SN,2,0,str);  
  sGpsn = str;
  dtostrf(SR,3,0,str);  
  sRads = str;
  //-------------------------------------------------------------------------
}




void setup() 
{
  //-----------------------------------------
  Serial.begin(115200);
  mySerial.begin(9600);
  GpsSerial.begin(4800);
  delay(1000);
  //-----------------------------------------
  Serial.println("BBK_GPS_GPRS");
  LcdIntShow();
  //-----------------------------------------
}
//-------------------------------------------
unsigned long NoowTime = 0;
unsigned long ShowTime = 0;
int ShowTimeKey = 1000;//5s
//-------------------------------------------
void loop() 
{
  //-----------------------------------------
  NoowTime = millis();
  //-----------------------------------------
  feedgps();
  //-----------------------------------------
  if( NoowTime - ShowTime > ShowTimeKey){ 
    ShowTime = NoowTime;
    //---------------------------------------
    Serial.println(NoowTime);
    GpsValueRun();
    //GpsLCDShow();
    //SerialShow();
    //SubmitHttpRequest(myurl,10);
    //---------------------------------------
  }
  //-----------------------------------------
}

void LcdIntShow(){
  myGLCD.InitLCD(50);
  //----------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("GPS Read Start", CENTER, 14); 
  myGLCD.print("(C)2013 by", CENTER, 36);
  myGLCD.print("BOBOKing.COM", CENTER, 42);
  myGLCD.update();
  //----------------------------------------------
  delay(1000); 
  //----------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("BBK_GPS_GPRS", CENTER, 10); 
  myGLCD.print("DataUp Start", CENTER, 24); 
  myGLCD.update();
  delay(1000); 
  //----------------------------------------------
}

void SerialShow(){
  //---------------------------------------------------
  Serial.println("----");
  //-------------------------
  Serial.println(tDate);
  Serial.println(sLats);
  Serial.println(sLons);
  //-------------------------
  Serial.print(sHigh);
  Serial.print(" ");
  Serial.print(sSped);
  Serial.print(" ");
  Serial.print(sFans);
  Serial.println();
  //-------------------------
  Serial.print(cLock);
  Serial.print(" ");
  Serial.print(cType);
  Serial.print(" ");
  Serial.print(sGpsn);
  Serial.print(" ");
  Serial.print(sRads);
  Serial.print(" ");
  Serial.print(sSeal);
  Serial.println();
  //---------------------------------------------------
}



void GpsLCDShow(){
  //------------------------------------------------
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  //------------------------------------------------
  myGLCD.print(sDate,0,  0);
  myGLCD.print(sTime,36,  0);
  //------------------------------------------------
  myGLCD.print("W",  0,  9);  
  myGLCD.print(sLats, 18,  9);  
  myGLCD.print("J",  0, 18);  
  myGLCD.print(sLons, 12, 18);
  //------------------------------------------------
  myGLCD.print("H", 0, 27);  
  myGLCD.print(sHigh, 8, 27);
  myGLCD.print("S", 46, 27); 
  myGLCD.print(sGpsn, 52, 27);  
  myGLCD.print(sRads, 66, 27);   
  ////------------------------------------------------
  myGLCD.print("V",  0, 36); 
  myGLCD.print(sSped,  8, 36); 
  myGLCD.print(cLock,  34, 36); 
  myGLCD.print(cType,  40, 36); 
  myGLCD.print("F",  46, 36); 
  myGLCD.print(sFans, 54, 36); 
  //------------------------------------------------
  myGLCD.update();
  //------------------------------------------------
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

//String myurl ="http://www.boboking.com/v/g.php?n=boboking&p=123xjp&g=38,112,50,46,80,99,1245678900000";
//String myurl ="www.boboking.com/!wap/index.htm";
//String myurl ="www.google.com.hk";

String CSQ = "AT+CSQ";
String CGA = "AT+CGATT?";
String SAP = "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"";//setting the SAPBR, the connection type is using gprs
String APN = "AT+SAPBR=3,1,\"APN\",\"CMNET\"";//setting the APN, the second need you fill in your local apn server
String PBR = "AT+SAPBR=1,1";//setting the SAPBR, for detail you can refer to the AT command mamual
String HTP = "AT+HTTPINIT"; //init the HTTP request
String URL = "AT+HTTPPARA=\"URL\",\""+myurl+"\"";//setting the httppara
String ACT = "AT+HTTPACTION=0";//submit the request 
String REA = "AT+HTTPREAD"; //read the data from the website you access
String REAT = "AT+HTTPREAD=0,1000";


void SubmitHttpRequest(String myurl,int delaysecond)
{
  //---------------------------------------------------------------
  URL = "AT+HTTPPARA=\"URL\",\""+myurl+"\"";//setting the httppara
  //---------------------------------------------------------------  
  mySerial.println(CSQ);  
  delay(100);    
  ShowSerialData();  
  mySerial.println(CGA);  
  delay(100);    
  ShowSerialData(); 
  mySerial.println(SAP);  
  delay(1000);   
  ShowSerialData(); 
  mySerial.println(APN);  
  delay(3000);   
  ShowSerialData();
  //mySerial.println(PBR);  delay(2000);  ShowSerialData();
  //mySerial.println(HTP);  delay(2000);  ShowSerialData();
  mySerial.println(URL);  
  delay(1000);   
  ShowSerialData();
  mySerial.println(ACT);  
  delay(delaysecond*1000);  
  ShowSerialData();
  //---------------------------------------------------------------
  //the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!mySerial.available()); 
  ShowSerialData();
  //---------------------------------------------------------------
  mySerial.println(REA);  
  delay(2000);   
  ShowSerialData(); 
  //---------------------------------------------------------------
  mySerial.println("");   
  delay(1000);
  //---------------------------------------------------------------
}

void ShowSerialData()
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
}

// if(Serial.available())
// {
//    unsigned char input = Serial.read();
//    mySerial.write(input); 
// }
// if( mySerial.available())
//{ 
//    unsigned char input2 = mySerial.read();
//    Serial.write(input2);
//}





