#include "SIM900.h"
#include <SoftwareSerial.h>
//#include "inetGSM.h"
#include "sms.h"
//#include "call.h"

#include <string.h>

#include <TinyGPS.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 3(rx) and 4(tx).
*/

TinyGPS gps;

#define ledpin 13
#define pwrkey 27

//**************************************************************************
char sms_rx[122]; //Received text SMS
byte type_sms=SMS_ALL;      //Type of SMS
byte del_sms=1;                //0: No deleting sms - 1: Deleting SMS
char number_incoming[20];
//**************************************************************************
SMSGSM sms;
int error;
boolean started=false;
bool newData = false;

char gps_year[8];
char gps_mon[3];
char gps_day[3];
char gps_hour[3];
char gps_min[3];
char gps_sec[3];


char gps_lon[20];
char gps_lat[20];

char gps_sms[100];


void setup()
{

//software power sim900 up

  pinMode(pwrkey,OUTPUT);
  digitalWrite(pwrkey,HIGH);
  delay(600);
  digitalWrite(pwrkey,LOW);
  
  
  Serial.begin(115200);
  Serial2.begin(9600);
     if (gsm.begin(9600)) {
          Serial.println("\nstatus=READY");
          gsm.forceON();        //To ensure that SIM908 is not only in charge mode
          started=true;
     } else Serial.println("\nstatus=IDLE");

  if(started)
  {
        //delete all sms message
        
        Serial.println("Deleting SMS");
        char error = DeleteAllSMS();
        if (error==1)Serial.println("All SMS deleted");      
    else Serial.println("SMS not deleted"); 

  
  }
  else
  {Serial.println("SIM900 NOT EXISTED"); while(1);}
  delay(10000);
  
}

void loop()
{

        if(started)
        {
        
                check_gps();
                Check_SMS();
        
        }





}



 void Check_SMS()  //Check if there is an sms 'type_sms'
 {
     char pos_sms_rx;  //Received SMS position     
     pos_sms_rx=sms.IsSMSPresent(type_sms);
     if (pos_sms_rx!=0)
     {
       //Read text/number/position of sms
       sms.GetSMS(pos_sms_rx,number_incoming,sms_rx,120);
       Serial.print("Received SMS from ");
       Serial.print(number_incoming);
       Serial.print("(sim position: ");
       Serial.print(word(pos_sms_rx));
       Serial.println(")");
       Serial.println(sms_rx);
       if (del_sms==1)  //If 'del_sms' is 1, i delete sms 
       {
         error=sms.DeleteSMS(pos_sms_rx);
         if (error==1)Serial.println("SMS deleted");      
         else Serial.println("SMS not deleted");

       }
                if((strstr(sms_rx,"gps")!=0)&&(strlen(sms_rx)==3))
                {
                                        Serial.println("\nsending SMS");
                                if(newData)
                                {
                                        if (sms.SendSMS(number_incoming, gps_sms))
                                        Serial.println("\nSMS sent OK");
                                        else
                                        Serial.println("\nSMS sent error");        
                                }
                                else
                                {
                                        if (sms.SendSMS(number_incoming, "gps not ready"))
                                        Serial.println("\nSMS sent OK");
                                        else
                                        Serial.println("\nSMS sent error");                                                
                                }
                                
                }
        Serial2.flush();
                
     }
         newData=false;
     return;
 }
 
 
char check_gps()
{
  newData=false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial2.available())
    {
      char c = Serial2.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    int _year;
    byte _month, _day,_hour,_minute,_second,_hundredths;        
    gps.f_get_position(&flat, &flon, &age);
        gps.crack_datetime(&_year,&_month,&_day,&_hour,&_minute,&_second,&_hundredths,&age);
        flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
        flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
    dtostrf(flat, 11, 6, gps_lat); 
    dtostrf(flon, 10, 6, gps_lon); 
        
        strcpy(gps_sms,"lat:");
        strcat(gps_sms,gps_lat);
        strcat(gps_sms,"\n");
        strcat(gps_sms,"lon:");
        strcat(gps_sms,gps_lon);
        strcat(gps_sms,"\n");
        strcat(gps_sms,"time:");
        
    itoa(_year,gps_year,10);
    strcat(gps_sms,gps_year);
        
    itoa(_month,gps_mon,10);
    if(strlen(gps_mon)==1)
      strcat(gps_sms,"0");
    strcat(gps_sms,gps_mon);
        
    itoa(_day,gps_day,10);
        if(strlen(gps_day)==1)
      strcat(gps_sms,"0");
    strcat(gps_sms,gps_day);
        
    itoa(_hour,gps_hour,10);
        if(strlen(gps_hour)==1)
      strcat(gps_sms,"0");
    strcat(gps_sms,gps_hour);
        
    itoa(_minute,gps_min,10);
        if(strlen(gps_min)==1)
      strcat(gps_sms,"0");
    strcat(gps_sms,gps_min);
        
    itoa(_second,gps_sec,10);
        if(strlen(gps_sec)==1)
      strcat(gps_sms,"0");
    strcat(gps_sms,gps_sec);        
        
    Serial.println(gps_sms);


  }
  



}
 
char DeleteAllSMS()
{
     char ret_val = -1;


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
 