/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
String comdata = "";
void Call_Phone(void);
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  delay(200);
}

void loop() // run over and over
{
  delay(2000);
  Call_Phone();
   mySerial.listen();
   while(1)
  {  
    while(mySerial.available()>0)  
        Serial.write(mySerial.read());
   while(Serial.available())
    mySerial.write(Serial.read());  //Arduino send the sim808 feedback to computer     
  } 
}

void Call_Phone(void)//sned message 
{
   mySerial.println("AT");//Send AT command     
   delay(500);  
  //Make a phone call
   mySerial.println("ATD13911969356;");//Change the receiver phone number   
   delay(200);
}

