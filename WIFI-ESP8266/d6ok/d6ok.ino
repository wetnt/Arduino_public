//http://www.ocrobot.com/doku.php?id=zh:ocrobot:modules:seed:at
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);

  Serial.println("begin...");
  delay(1000);

  ATSend("AT+ID", "done");
  delay(2000);
  ATSend("AT+MODE?", "done");
  delay(2000);
  ATSend("AT+JoinAP?", "done");
  delay(1000);
  ATSend("AT+ShowIP", "done");
  delay(1000);
  ATSend("AT+NewSTA=\"TCP\",\"www.baidu.com\",80", "Linked");
  delay(1000);
  ATSend("AT+ShowSTA", "done");
  delay(2000);
  ATSend("AT+MUX=1", "done");
  delay(2000);



  NetSend("GET / HTTP/1.1 \r\nHost: 61.135.169.121 \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n");
  //delay(1000);
}

void ATSend(String cmd, String back) {
  Serial1.println(cmd);
  Serial.println(cmd);
  waitBack(back);
}

int wbn = 0;
void waitBack(String str) {
  //------------------------
  //bool backkey = false;
  //------------------------
  String data;
  while (1) {
    if (Serial1.available() > 0)
    {
      char a = Serial1.read();
      data = data + a;
      Serial.print(a);
      wbn++;
    }
    if (data.indexOf("busy") != -1)
    {
      Serial.println("=busy");
      break;
    }
    if (data.indexOf("ERROR") != -1)
    {
      Serial.print(str);
      Serial.println("=ERROR");
      break;
    }
    if (data.indexOf(str) != -1)
    {
      Serial.print(str);
      Serial.println("=ok");
      break;
    }
    if (wbn > 500) {
      wbn = 0;
      Serial.println("timeout");
      break;
    }
  }
  //------------------------
}

void NetSend(String x) {
  int n = x.length() + 1;
  String s = String("AT+UpDate=") + String(n);
  ATSend(s, ">"); //delay(1000);
  ATSend(x, "SEND OK");
}

int dn = 0;
void loop() {
  if (Serial1.available() > 0)
  {
    char a = Serial1.read();
    Serial.print(a);
    dn++;
    //-------------------------------------------------------------
    if (dn > 48) {
      dn = 0;
      //NTPTime_Exp();
      //NTPTime_Set();
      //NTPTime_show();
    }
    //-------------------------------------------------------------
  }
  //ppp();
  //delay(5000);
}


