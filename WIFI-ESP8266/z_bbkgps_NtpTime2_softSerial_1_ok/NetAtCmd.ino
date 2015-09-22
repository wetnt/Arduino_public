//http://www.ocrobot.com/doku.php?id=zh:ocrobot:modules:seed:at
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=12492&highlight=8266

String ssid = "MMMM";
String pass = "1234567890123";
boolean key = true;

void NetInit() {
  ATSend("AT", "OK", "", 10, key);            loopSerial1(); delay(1000); loopSerial1();
  //ATSend("AT+CWMODE=1", "OK", "no change", 10, key);  loopSerial1(); delay(1000); loopSerial1();
  //ATSend("AT+RST", "ready", "invalid", 20, key);      loopSerial1(); delay(1000); loopSerial1();
  String jionAP = "AT+CWJAP=\"" + ssid + "\",\"" + pass +"\"";
  ATSend(jionAP, "OK", "", 10, key); loopSerial1(); delay(2000); loopSerial1();
  ATSend("AT+CWJAP?", "OK", "", 10, key);     loopSerial1(); delay(1000); loopSerial1();
  ATSend("AT+CIFSR", "OK", "", 10, key);      loopSerial1(); delay(1000); loopSerial1();
}


void NetATStart() {
  ATSend("AT", "OK", "", 10, key);            loopSerial1(); delay(1000); loopSerial1();
  ATSend("AT+CWJAP?", "OK", "", 10, key);     loopSerial1(); delay(1000); loopSerial1();
  ATSend("AT+CIFSR", "OK", "", 10, key);      loopSerial1(); delay(1000); loopSerial1();
}


void ATSend( String cmd, String backA, String backB, int TimeOutSecond, boolean backKey) {
  SoftSerialPrintln(cmd);
  if (backA.length() > 0)
    NetWaitBack(  backA, backB, TimeOutSecond, backKey);
}

long wTime = millis();
long wTimeKey = 10 * 1000;
String NetWaitBack(String strA, String strB, int TimeOutSecond, boolean backKey) {
  //------------------------------------------------
  wTimeKey = TimeOutSecond * 1000;
  wTime = millis();
  //------------------------------------------------
  String data;
  while (1) {
    //-----------------------------------
    if (SoftSerialAvailable())
    {
      char a = SoftSerialRead();
      data = data + a;
      if (backKey)
        SerialPrint(a);
    }
    //-----------------------------------
    if (DataIndexOf(data, "busy", backKey ))break;
    if (DataIndexOf(data, "ERROR", backKey))break;
    if (strB.length() > 0) {
      if (DataIndexOf(data, strA, backKey)) data = "";
      if (DataIndexOf(data, strB, backKey)) return data;
    } else {
      if (DataIndexOf(data, strA, backKey)) return "";
    }
    //-----------------------------------
    if ( millis() - wTime > wTimeKey ) {
      if (backKey)
        SerialPrintln("timeout");
      break;
    }
    //-----------------------------------
  }
  //------------------------------------------------
}

boolean DataIndexOf(String d, String s, boolean backKey) {
  //------------------------------------------------
  if (d.indexOf(s) != -1)
  {
    if (backKey) {
      SerialPrint('=');SerialPrintln(s);
    }
    return true;
  } else {
    return false;
  }
  //------------------------------------------------
}

void NetSend(String x) {
  //------------------------------------------------
  int n = x.length() + 2;
  String s = String("AT+CIPSEND=") + String(n);
  ATSend(s, ">", "", 20, key);
  ATSend(x, "SEND OK", "", 20, key);
  //------------------------------------------------
}

void loopSerial1() {
  while (SoftSerialAvailable() > 0) {
    char a = SoftSerialRead();
    SerialPrint(a);
  }
}
