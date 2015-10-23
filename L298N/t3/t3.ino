#include <SoftwareSerial.h>
SoftwareSerial myCmds(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  myCmds.begin(9600);
  BKMOTO(4,5,6,7,8,9);
  Serial.println("$JML,CAR,SAN,10,0,0,0,0,0;");
}

void loop() {
  //-----------------------
  SerialRead();
  //-----------------------------
  CmdRead();
  //-----------------------  
}

void SerialRead()
{
  //-------------------------------------------------------------------------
  while (Serial.available()>0)
  {
    //CmdExp(Serial.read());    
  }
  //-------------------------------------------------------------------------
}

void CmdRead()
{
  //-------------------------------------------------------------------------
  while (myCmds.available()>0)
  {
    CmdExp(myCmds.read());    
  }
  //-------------------------------------------------------------------------
}






