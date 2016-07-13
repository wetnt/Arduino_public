#include <SoftwareSeriala.h>
SoftwareSerial myS(11, 10); //rx tx

void setup() {

  Serial.begin(9600);
  myS.begin(9600);
  delay(1000);
  Serial.println("begin...");
  delay(5000);

  ATSend("AT+ID", "done");
  delay(1000);
  ATSend("AT+JoinAP?", "JoinAP");
  delay(1000);
  ATSend("AT+ShowIP", "done");
  delay(1000);
  ATSend("AT+NewSTA=\"UDP\",\"192.168.1.100\",8080", "done");
  delay(1000);
  ATSend("AT+UpDate=10", ">");
  delay(1000);
  ATSend("boboking123", "SEND OK");
  delay(1000);
}

void ATSend(String cmd, String back) {
  Serial.println(cmd);
  myS.println(cmd);
  waitBack(back, true);
}


void waitBack(String str, bool backkey) {
  //------------------------
  //bool backkey = false;
  if (backkey) {
    Serial.print("wait--");
    Serial.println(str);
  }
  //------------------------
  String data;
  while (1) {
    if (myS.available() > 0)
    {
      char a = myS.read();
      data = data + a;
      if (backkey) {
        Serial.print(a);
      }
    }
    if (data.indexOf(str) != -1)
    {
      if (backkey) {
        Serial.println("_ok");
      }
      break;
    }
    if (data.indexOf("ERROR") != -1)
    {
      if (backkey) {
        Serial.println("_ERROR");
      }
      break;
    }
    //Serial.print(".");
  }
  //------------------------
}

void NetSend(String x) {
  int n = x.length() + 1;
  String s = String("AT+UpDate=") + String(n);
  ATSend(s, ">"); //delay(1000);
  ATSend(x, "SEND OK");
}

void loop() {
  long t = millis();
  String s = String(t);
  NetSend(s); delay(2000);
  NetSend("BOBOKing1234567890"); delay(2000);
}


