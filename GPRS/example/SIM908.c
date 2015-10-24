http://www.arduino.cn/thread-6872-1-1.html

#include "SIM900.h"
#include <SoftwareSerial.h>
//#include "inetGSM.h"
#include "sms.h"
//#include "call.h"
#include "gps.h"
#include <string.h>
 
//To change pins for Software Serial, use the two lines in GSM.cpp.
 
//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs.
 
//Simple sketch to start a connection as client.
 
//InetGSM inet;
//CallGSM call;
SMSGSM sms;
GPSGSM gps;
 
char lon[15];
char lat[15];
char alon[15];
char alat[15];
char alt[15];
char time[20];
char vel[15];
char msg1[5];
char msg2[5];
char str1[80];
char stat;
char inSerial[20];
int i=0;
boolean started=false;
char smsbuffer[160];
//char number[20];
char n[20];
#define ledpin 13
byte type_sms=SMS_ALL;
 
//#define READ_TIMEOUT 300000
 
//int powerpin=7; 自动开机，p连接到D7，取消该注释即可
 
void setup()
{
 
  //pinMode(powerpin,OUTPUT); 需要自动开机，取消该注释即可
  //digitalWrite(powerpin,HIGH);需要自动开机，取消该注释即可
  //delay(1000);需要自动开机，取消该注释即可
  //digitalWrite(powerpin,LOW);需要自动开机，取消该注释即可
  //delay(10000); 需要自动开机，取消该注释即可
 
     //Serial connection.
     Serial.begin(9600);
     Serial.println("GSM Shield testing.");
     pinMode(ledpin,OUTPUT);
     //Start configuration of shield with baudrate.
     //For http uses is raccomanded to use 4800 or slower.
     if (gsm.begin(4800)) {
          Serial.println("\nstatus=READY");
          gsm.forceON();    //To ensure that SIM908 is not only in charge mode
          started=true;
     } else Serial.println("\nstatus=IDLE");
 
     if(started) {
         Serial.println("Deleting SMS");
            char error = DeleteAllSMS();
         if (error==1)Serial.println("All SMS deleted");      
         else Serial.println("SMS not deleted");
          //GPS attach
          if (gps.attachGPS())
               Serial.println("status=GPSREADY");
          else Serial.println("status=ERROR");
 
          delay(10000); //Time for fixing
          //long start = millis();
         // while(millis() < (start + READ_TIMEOUT))
         // {
 
          //delay(20000);
          //Get data from GPS
 
          //}
     }
 
};
 
void loop()
{
     if(started) {
          //Read if there are messages on SIM card and print them.
          //if(gsm.readSMS(smsbuffer, 80, n, 20)) {
            char pos_sms_rx;  //Received SMS position     
            pos_sms_rx=sms.IsSMSPresent(type_sms);
            if (pos_sms_rx!=0){
            sms.GetSMS(pos_sms_rx,n,smsbuffer,160);
            Serial.println(n);
            Serial.println(smsbuffer);
            char error=sms.DeleteSMS(pos_sms_rx);
            if (error==1)Serial.println("SMS deleted");      
            else Serial.println("SMS not deleted");
            if((strstr(smsbuffer,"gps")!=0)&&(strlen(smsbuffer)==3))
            {
                //strcpy(number,n);
          stat=gps.getStat();
           
          if(stat==1)
          {
               Serial.println("NOT FIXED");
 
            }
                
          else if(stat==0)
          {
               Serial.println("GPS OFF");
            
               }
          else if(stat==2)
          {
               Serial.println("2D FIXED");
            
         }
          else if(stat==3)
          {
               Serial.println("3D FIXED");
                            
          }
               gps.getPar(lon,lat,alt,time,vel);
               double _longitude = stringtofloat(lon);
               double _latitude = stringtofloat(lat);
               floattostring(_longitude, alon);
               floattostring(_latitude, alat);
               strcpy(str1,"lon:");
               strcat(str1,alon);
               strcat(str1,"\n");
               strcat(str1,"lat:");
               strcat(str1,alat);
               strcat(str1,"\n");
              // strcat(str1,alt);
              // strcat(str1,"\n");
               strcat(str1,"time:");
               strcat(str1,time);
               strcat(str1,"\n");
              // strcat(str1,vel);
                if(stat <3)
                {
                    if (sms.SendSMS(n, "gps not ready"))
                    Serial.println("\nSMS sent OK");
                }
                else
                {
                    if (sms.SendSMS(n, str1))
                    Serial.println("\nSMS sent OK");                    
                }
 
                 
            }
            else
            {
                Serial.println("message not correct");
            }
          }
          delay(1500);
        stat=gps.getStat();
        Serial.println(lon);
        Serial.println(lat);
        Serial.println(alt);
        Serial.println(time);
        Serial.println(vel);        
        if(stat>2)
        {
            digitalWrite(ledpin,HIGH);          
        }
        else
         digitalWrite(ledpin,LOW);
          
 
     }
};
 
double stringtofloat(char *latString)
{
     double latitude = atof(latString);                                    // convert to a double (precise)
     int deg = (int) latitude / 100;                               // extract the number of degrees
     double mine = latitude - (100 * deg);                  // work out the number of minutes
     latitude = deg + (double) mine/60.0;                   // convert to decimal format
     return latitude;
}
 
double floattostring(double lvalue, char *lstring)
{
  char _null[1];
  int intvalue = (int) lvalue;
  itoa(intvalue,lstring,10);
  strcat(lstring, ".");
  double mm = lvalue -intvalue;
   
  for(char a=0;a<6;a++)
  {
    mm=mm*10;
    int bb = (int)mm;
    itoa(bb,_null,10);
    strcat(lstring, _null);
    mm = mm-bb;
  }
 
}
 
char DeleteAllSMS()
{
     char ret_val = -1;
     char *p_char;
     byte status;
 
     if (CLS_FREE != gsm.GetCommLineStatus()) return (ret_val);
     gsm.SetCommLineStatus(CLS_ATCMD);
     ret_val = 0; // still not present
      
     gsm.SimpleWriteln(F("AT+CMGDA=\"DEL ALL\""));
      
     switch (gsm.WaitResp(8000, 50, "OK")) {
     case RX_TMOUT_ERR:
          // response was not received in specific time
          ret_val = -2;
          break;
 
     case RX_FINISHED_STR_RECV:
          // OK was received => SMS deleted
          ret_val = 1;
          break;
 
     case RX_FINISHED_STR_NOT_RECV:
          // other response: e.g. ERROR => SMS was not deleted
          ret_val = 0;
          break;
     }
 
     gsm.SetCommLineStatus(CLS_FREE);
     return (ret_val);   
}