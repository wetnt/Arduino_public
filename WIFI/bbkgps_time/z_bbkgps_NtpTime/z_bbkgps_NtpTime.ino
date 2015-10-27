//http://www.ocrobot.com/doku.php?id=zh:ocrobot:modules:seed:at
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=12492&highlight=8266
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);

  Serial.println("begin...");
  delay(1000);

  ATSend("AT", "OK");  delay(200);
  ATSend("AT+RST", "ready");  delay(200);
  ATSend("AT+CWMODE=1", "OK"); delay(200);
  ATSend("AT+CWJAP=\"MMMM\",\"1234567890123\"", "OK");  delay(200);
  ATSend("AT+CWJAP?", "OK");  delay(200);
  ATSend("AT+CIPSTART=\"TCP\",\"www.bbkgps.com\",80", "Linked"); delay(200);
  ATSend("AT+CIPMODE=1", "OK"); delay(200);
  
 
  ATSend("AT+CIPSEND", "OK"); delay(200);

  //  Serial1.println("GET / HTTP/1.1 \r\nHost: www.bbkgps.com \r\nUser-Agent: abc \r\nConnection: close \r\n\r\n");
  //  Serial1.println("");

  //  Serial1.print("GET /index.htm HTTP/1.1\n");delay(20);
  //  Serial1.print("Host:www.bbkgps.com\n");delay(20);
  //  Serial1.print("User-Agent:abc\n");delay(20);
  //  Serial1.print("Connection:close\n");delay(20);
  //  Serial1.print("\n");delay(20);
  //  Serial1.print("\n");delay(20);
  //  char s4 = 0x1A;
  //  Serial1.print(s4);delay(20);
  //  Serial1.print(0x1a);delay(20);
  //  Serial1.print("AT");delay(20);


  String cmd = "";
  cmd += "GET /index.htm HTTP/1.0\r\n";
  cmd += "Host: www.bbkgps.com\r\n";
  cmd += "User-Agent: abc\r\n";
  cmd += "Accept: */*\r\n";
  cmd += "Connection: close\r\n";
  cmd += "\r\n";
  //Serial1.print(cmd); delay(20);
  char s4 = 0x1A;
  //Serial1.print(s4); delay(20);
  //Serial1.print(0x1a); delay(20);
  //Serial1.print("AT"); delay(20);


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
  String s = String("AT+CIPSEND=0,") + String(n);
  ATSend(s, ">"); //delay(1000);
  ATSend(x, "SEND OK");
}

int dn = 0;
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
