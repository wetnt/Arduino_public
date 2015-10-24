
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "gps.h"
#include "inetGSM.h"
#include "sms.h"

#include <math.h>
//#include <errno.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SMSGSM sms;
InetGSM inet;
GPSGSM gps;

boolean started=false;
char messagearray[100];
    char number[20];
    char sende[20]="+919490974707"; // Athenticator mob
    char message[180];
 
void setup()
{
     //Serial connection.
     Serial.begin(9600);
     Serial.println("GSM Shield testing.");
     if (gsm.begin(9600)) {
          Serial.println("\nstatus=READY");
          gsm.forceON();	//To ensure that SIM908 is not only in charge mode
          started=true;
     } else Serial.println("\nstatus=IDLE");

     if(started) {
          //GPS attach
          if (gps.attachGPS())
               Serial.println("status=GPSREADY");
         else Serial.println("status=ERROR");
          delay(5000);
          
         if (inet.attachGPRS("internet.wind", "", ""))
               Serial.println("status=ATTACHED");
          else Serial.println("status=ERROR");
          delay(1000);

          //Read IP address.
          gsm.SimpleWriteln("AT+CIFSR");
          delay(1000);
          //Read until serial buffer is empty.
          gsm.WhileSimpleRead();

          //TCP Client GET, send a GET request to the server and
          //save the reply.
         // numdata=inet.httpGET("www.google.com", 80, "/", msg, 50);
          //Print the results.
      //    Serial.println("\nNumber of data received:");
       //   Serial.println(numdata);
        //  Serial.println("\nData received:");
       //   Serial.println(msg);/**/
      //  inet.dettachGPRS(); 
     }
}

void clearbuf(char *b)// clearing the buffer
{
  while(*b)
    *b++='\0';
}

void gpsinfo()
{
      char lon[10];
      char lat[10];
      char alt[10];
      char sat[5];
      
      gps.getPar(lat, lon, alt, sat);
      Serial.print("lat: ");
      Serial.println(lat);
      Serial.print("lon: ");
      Serial.println(lon);
      Serial.print("alt: ");
      Serial.println(alt);    
      
      strcat(messagearray,lat);
      strcat(messagearray,"@");
      strcat(messagearray,lon);
      strcat(messagearray,"@"); 
      strcat(messagearray,alt);
      strcat(messagearray,"@"); 
}

void getdata()
{
      gpsinfo();
      delay(100);
      
      //   if (inet.attachGPRS("internet.wind","", ""))
        //       Serial.println("status=ATTACHED");
         // else Serial.println("status=ERROR");
         
         // gsm.SimpleWriteln("TEST");
       //inet.httpPOST("54.179.134.139", 3001, "/","TEST", "GPRS ", 50);
        //  delay(5000);
        //inet.dettachGPRS(); 
  if (sms.SendSMS("9490974707", "O.K"))
      Serial.println("\nSMS sent OK");      
}

void loop()
{
    char c[10],d[10]; 
    int p,g,s,j,k,e,i=0,m;
    char pos;

   pos=sms.IsSMSPresent(SMS_UNREAD);// we can check msg recvd or not
 
  // delay(3000);
 
   if((int)pos>=1&&(int)pos<=20){
 
   Serial.print("POS=");
 
   Serial.println((int)pos);
 
   message[0]='\0';
 
   sms.GetSMS((int)pos,number,message,180);// getting the num&mesg
   delay(500);
   //Serial.println(number);
   //Serial.println(message);
  // delay(3000);
   
   if(number[0])// if number recived or not checking
   {
     p=strcmp(number,sende); //checking the number 
   
     if(!p)// if known number
     {
        Serial.println("Authorised Person\n"); 
        Serial.print("Mobile Number: ");
        Serial.println(number);   
        Serial.println(" ");        
        Serial.print("Message: ");
        Serial.println(message); 
        Serial.println(" ");  
        
          while(message[i]!='@')
            {
                c[j]=message[i];
                i++;
                j++;
            }
            i++;
            c[j]='\0';
            while(message[i]!='\0')
            {
                d[k]=message[i];
                i++;
                k++;
            }  
            d[k]='\0';
            
           m=atoi(d);
           g=strcmp(c,"getdata");
           s=strcmp(c,"setdata");
           e=strcmp(c,"seteeprom");
                   
           if(!g)
           { 
              getdata();
           }
           if(!s)
           {
            // setdata(m);  
           }
           if(!e)
           {
             //seteeprom(m);
           }
     sms.DeleteSMS((int)pos);
     Serial.println("Message Deleted\n");
   }//if(number[0])
  }//if(pos)
 }
  
   //delay(1000); 
   /*** clearing all variables***/ 
  // for(i=0;i<10;i++)
   //sms.DeleteSMS(i);
  // Serial.println("Message Deleted\n");
   clearbuf(message);
   clearbuf(number);
   clearbuf(c);
   clearbuf(d);
   clearbuf(messagearray);
   p='\0';
   g='\0';
   s='\0';
   i='\0';
   j='\0';
   k='\0';
   m='\0';
   delay(2000);
}//loop()

void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
    while (i < d)
        str[i++] = '0';
    reverse(str, i);
    str[i] = '\0';
    return i;
}
void ftoa(float n, char *res, int afterpoint)
{
    int ipart = (int)n;
    float fpart = n - (float)ipart;
    int i = intToStr(ipart, res, 0);
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
        fpart = fpart * pow(10, afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
};
