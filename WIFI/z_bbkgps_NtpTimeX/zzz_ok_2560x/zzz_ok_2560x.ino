#include <Event.h>
#include <Timer.h>
Timer t;
//=====================================================
String ts = "";
//=====================================================
String netLink = "AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80";
String cmdHttp = "GET /t.php HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n";
//=====================================================
void setup() {
  //----------------------------------
  Serial.begin(9600);  delay(1000);
  Serial1.begin(9600); delay(1000);
  EchoSerialPrintln("begin...");
  //----------------------------------
  Tube_Setup();
  //----------------------------------
  NetATStart(false);
  //----------------------------------
  int t1 = t.every(20000, NetLoop2);
  SerialNext(1);
  //----------------------------------
}

int stepKey = 0;
void SerialNext(int k) {

  if (k == 1 || k == 4 || k == 5) {
    stepKey++;
  } else {
    return;
  }

  EchoSerialPrintln("");
  EchoSerialPrint("key=");
  EchoSerialPrint(k);
  EchoSerialPrint(" setp=");
  EchoSerialPrintln(stepKey);

  if (stepKey == 1) {
    //SerialWaitSet( "Linked", "CONNECT", 10, true);
    SerialWaitSet( "CONNECT", "", 10, false);
    Serial1.println(netLink);
  }
  
  if (stepKey == 2) {
    int n = cmdHttp.length() + 2;
    String s = String("AT+CIPSEND=") + String(n);
    SerialWaitSet( ">", "", 20, false); WorkSerialPrintln(s);
  }
  if (stepKey == 3) {
    SerialWaitSet( "SEND OK", "", 20, false); WorkSerialPrintln(cmdHttp);
  }
  if (stepKey == 4) {
    SerialWaitSet( "Time=", ";", 20, false);WorkSerialPrintln("");
    //serialClear();
  }
  if (stepKey == 5) {
    ts = SerialWaitBack();
    EchoSerialPrintln(ts);
    StringToTimeSet(ts);
  }

}

void NetLoop2(){
  stepKey = 0;
  SerialNext(1);
}
void NetLoop() {
  //----------------------------------
  ATSend(netLink, "Linked", "CONNECT", 10);
  loopSerial1(); delay(100);
  NetSend(cmdHttp);
  String sss = NetWaitBack("DateTime=", ";", 10);
  Serial.println(sss);
  //----------------------------------
}

void loop() {
  //----------------------------------
  t.update();
  //----------------------------------
  SerialWaitLoop();
  //----------------------------------
  Tube_Loop();
  //----------------------------------
}

void serialClear() {
  //----------------------------------
  if (Serial.available() > 0)
  {
    char a = Serial.read();
    //Serial1.print(a);
  }
  //----------------------------------
  if (Serial1.available() > 0)
  {
    char a = Serial1.read();
    //Serial.print(a);
  }
  //----------------------------------
}
