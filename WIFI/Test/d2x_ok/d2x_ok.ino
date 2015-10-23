//------------------------------------------------
String ssid = "MMMM";
String pwd = "1234567890123";
//------------------------------------------------

void wifi_waiting(int n) {
  //------------------------------------------------
  Serial.print("wifi.");
  for (int i = 0; i < n; i++) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("ok");
  //------------------------------------------------
}

void delaySecond(int n) {
  delay(1000 * n);
}

void setup() {
  //------------------------------------------------
  ssid = "acDev";
  pwd = "AbroadCar2015()";
  //------------------------------------------------
  Serial.begin(9600);
  delaySecond(2);
  Serial.println("Arduino begin...");
  //------------------------------------------------
  Serial1.begin(9600);
  delaySecond(2);
  wifi_waiting(5);
  //------------------------------------------------
  ATSend("AT+ID", "done");
  //delaySecond(10);
  //------------------------------------------------
  ATSend("AT+JoinAP?", "JoinAP");
  //delaySecond(10);
  //------------------------------------------------
  String sss = String("AT+JoinAP=\"") + String(ssid) + String("\",\"") + String(pwd) + String("\"");
  Serial1.println(sss);
  delaySecond(20);
  //------------------------------------------------
  ATSend("AT+JoinAP?", "JoinAP");
  delaySecond(10);
  //------------------------------------------------
  ATSend("AT+ShowIP", "done");
  delaySecond(10);
  //------------------------------------------------
  //ATSend("AT+NewSTA=\"UDP\",\"172.16.102.60\",8888", "done");
  ATSend("AT+CIPSTART=\"TCP\",\"time.nist.gov\",13", "done");
  delaySecond(10);
  //------------------------------------------------
  ATSend("AT+UpDate=10", ">");
  delaySecond(10);
  //------------------------------------------------
  ATSend("boboking123", "SEND OK");
  delaySecond(10);
  //------------------------------------------------
}

void ATSend(String cmd, String back) {
  Serial.println(cmd);
  Serial1.println(cmd);
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
    if (Serial1.available() > 0)
    {
      char a = Serial1.read();
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
  //  long t = millis();
  //  String s = String(t);
  //  NetSend(s); delay(2000);
  //  NetSend("BOBOKing1234567890"); delay(2000);

  //------------------------------------------------
  //  ATSend("AT+JoinAP?", "JoinAP");
  //  delaySecond(10);
  //  ATSend("AT+ShowIP", "done");
  //  delaySecond(10);

  String sss = String("AT+JoinAP=\"") + String(ssid) + String("\",\"") + String(pwd) + String("\"");
  Serial1.println(sss);
  delaySecond(20);
  //------------------------------------------------
  //ATSend("AT+NewSTA=\"UDP\",\"172.16.102.60\",8888", "done");
  //delaySecond(10);
  ATSend("AT+CIPSTART=\"TCP\",\"time.nist.gov\",13", "done");
  delaySecond(10);
  delaySecond(50);
}


