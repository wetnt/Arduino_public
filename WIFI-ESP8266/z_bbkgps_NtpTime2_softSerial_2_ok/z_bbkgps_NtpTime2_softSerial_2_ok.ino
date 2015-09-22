//=====================================================
//#include "Timer.h"
//Timer t; 
//=====================================================
void setup() {
  
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(100);
  Serial.println("begin...");
  delay(100);

  //NetInit();
  NetATStart(false);

  ATSend("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80", "Linked", "CONNECT", 20, false); loopSerial1(false); delay(100);
  String cmd = "GET /time.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
  NetSend(cmd);
  String sss = NetWaitBack("DateTime", ";", 10, false);
  Serial.println(sss);
  
}

void loop() {
  if (Serial.available() > 0)
  {
    char a = Serial.read();
    //Serial1.print(a);
  }
  if (Serial1.available() > 0)
  {
    char a = Serial1.read();
    //Serial.print(a);
  }  
}
