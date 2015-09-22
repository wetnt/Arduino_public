//http://www.ocrobot.com/doku.php?id=zh:ocrobot:modules:seed:at
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=12492&highlight=8266

String ssid = "MMMM";
String pass = "1234567890123";
boolean backKey = false;

String testAT = "AT";
String jionAP = "AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"";
String seesAP = "AT+CWJAP?";
String seesIP = "AT+CIFSR";
String reStar = "AT+RST";
String toWiFi = "AT+CWMODE=1";

void NetInit(boolean keys) {
  //-----------------------------------------------------------------------
  backKey = keys;
  //-----------------------------------------------------------------------
  ATSend(testAT, "OK", "", 10); loopSerial1(); delay(1000);
  ATSend(jionAP, "OK", "", 10); loopSerial1(); delay(2000);
  ATSend(seesAP, "OK", "", 10); loopSerial1(); delay(1000);
  ATSend(seesIP, "OK", "", 10); loopSerial1(); delay(1000);
  //-----------------------------------------------------------------------
  //ATSend(toWiFi,  "OK", "no change",10,key); loopSerial1();delay(1000);
  //ATSend(reStar,"ready","invalid",  20,key); loopSerial1();delay(1000);
  //-----------------------------------------------------------------------
}


void NetATStart(boolean keys) {
  //-----------------------------------------------------------------------
  backKey = keys;
  //-----------------------------------------------------------------------
  ATSend(testAT, "OK", "", 10); loopSerial1(); delay(1000);
  ATSend(seesAP, "OK", "", 10); loopSerial1(); delay(1000);
  ATSend(seesIP, "OK", "", 10); loopSerial1(); delay(1000);
  //-----------------------------------------------------------------------
}


void ATSend(String cmd, String backA, String backB, int TimeOutSecond) {
  SoftSerialPrintln(cmd);
  if (backA.length() > 0) NetWaitBack(backA, backB, TimeOutSecond);
}

long wTime = millis();
long wTimeKey = 10 * 1000;
String NetWaitBack(String strA, String strB, int TimeOutSecond) {
  //------------------------------------------------
  wTimeKey = TimeOutSecond * 1000; wTime = millis();
  //------------------------------------------------
  String data;
  while (1) {
    //-----------------------------------
    if (SoftSerialAvailable())
    {
      char a = SoftSerialRead();
      data = data + a;
      if (backKey)SerialPrint(a);
    }
    //-----------------------------------
    if (DataIndexOf(data, "busy" ))break;
    if (DataIndexOf(data, "ERROR"))break;
    if (strB.length() > 0) {
      if (DataIndexOf(data, strA)) data = "";
      if (DataIndexOf(data, strB)) return data;
    } else {
      if (DataIndexOf(data, strA)) return "";
    }
    //-----------------------------------
    if ( millis() - wTime > wTimeKey ) {
      if (backKey) SerialPrintln("timeout");
      break;
    }
    //-----------------------------------
  }
  //------------------------------------------------
  return "";
  //------------------------------------------------
}

boolean DataIndexOf(String d, String s) {
  //------------------------------------------------
  if (d.indexOf(s) != -1)
  {
    if (backKey) {
      SerialPrint('=');
      SerialPrintln(s);
    }
    return true;
  } else {
    return false;
  }
  //------------------------------------------------
}

void NetSend(String x) {
  int n = x.length() + 2;
  String s = String("AT+CIPSEND=") + String(n);
  ATSend(s, ">", "", 20);
  ATSend(x, "SEND OK", "", 20);
}

void loopSerial1() {
  while (SoftSerialAvailable() > 0) {
    char a = SoftSerialRead();
    if (backKey)SerialPrint(a);
  }
}


