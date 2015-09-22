#include <Event.h>
#include <Timer.h>
Timer t;
//=====================================================
//=====================================================
String netLink = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
String cmdHttp = "GET /time.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
//=====================================================
void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);  delay(1000);
  Serial.println("begin...");
  delay(100);

  NetATStart(true);
  NetLoop();
  //int t1 = t.every(20000, NetLoop);
}

void NetLoop() {
  ATSend(netLink, "Linked", "CONNECT", 10, false);
  loopSerial1(false); delay(100);
  NetSend(cmdHttp);
  String sss = NetWaitBack("HTTP", "", 10, false);
  Serial.println(sss);
}

void loop() {
  if (Serial.available() > 0)
  {
    char a = Serial.read();
    Serial1.print(a);
  }
  if (Serial1.available() > 0)
  {
    char a = Serial1.read();
    Serial.print(a);
  }
  
  //t.update();
}
