#include "SIM900.h"
#include "gps.h"

GPSGSM gps;

char lon[15];
char lat[15];
char alt[15];
char time[20];
char vel[15];
char msg1[5];
char msg2[5];

char stat;
char inSerial[20];
int i=0;
boolean started=false;

void gsm_setup(){
     if (gsm.begin(9600)) {
          lg("\nstatus=READY");
          gsm.forceON();  //To ensure that SIM908 is not only in charge mode
          started=true;
     } else lg("\nstatus=IDLE");

     if(started) {
          //GPS attach
          if (gps.attachGPS())
               lgln("status=GPSREADY");
          else lgln("status=ERROR");

          delay(20000); //Time for fixing
          stat=gps.getStat();
          if(stat==1)
               lgln("NOT FIXED");
          else if(stat==0)
               lgln("GPS OFF");
          else if(stat==2)
               lgln("2D FIXED");
          else if(stat==3)
               lgln("3D FIXED");
          delay(5000);
          //Get data from GPS
          gps.getPar(lon,lat,alt,time,vel);
          Serial.println(lon);
          Serial.println(lat);
          Serial.println(alt);
          Serial.println(time);
          Serial.println(vel);
     }
};

void loop()
{
     //Read for new byte on serial hardware,
     //and write them on NewSoftSerial.
     serialhwread();
     //Read for new byte on NewSoftSerial.
     serialswread();
};

void serialhwread()
{
     i=0;
     if (Serial.available() > 0) {
          while (Serial.available() > 0) {
               inSerial[i]=(Serial.read());
               delay(10);
               i++;
          }

          inSerial[i]='\0';
          if(!strcmp(inSerial,"/END")) {
               Serial.println("_");
               inSerial[0]=0x1a;
               inSerial[1]='\0';
               gsm.SimpleWriteln(inSerial);
          }
          //Send a saved AT command using serial port.
          if(!strcmp(inSerial,"TEST")) {
//      Serial.println("BATTERY TEST 1");
//      gps.getBattInf(msg1,msg2);
//      Serial.println(msg1);
//      Serial.println(msg2);
//      Serial.println("BATTERY TEST 2");
//      gps.getBattTVol(msg1);
//      Serial.println(msg1);
               stat=gps.getStat();
               if(stat==1)
                    Serial.println("NOT FIXED");
               else if(stat==0)
                    Serial.println("GPS OFF");
               else if(stat==2)
                    Serial.println("2D FIXED");
               else if(stat==3)
                    Serial.println("3D FIXED");
          }
          //Read last message saved.
          if(!strcmp(inSerial,"MSG")) {
               Serial.println(msg1);
          } else {
               Serial.println(inSerial);
               gsm.SimpleWriteln(inSerial);
          }
          inSerial[0]='\0';
     }
}

void serialswread(){
     gsm.SimpleRead();
}
