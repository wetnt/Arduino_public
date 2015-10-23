//http://www.ocrobot.com/doku.php?id=zh:ocrobot:modules:seed:at
//http://www.geek-workshop.com/forum.php?mod=viewthread&tid=12492&highlight=8266

String ssid = "MMMM";
String pass = "1234567890123";
boolean key = false;

String testAT = "AT";
String jionAP = "AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"";
String seesAP = "AT+CWJAP?";
String seesIP = "AT+CIFSR";
String reStar = "AT+RST";
String toWiFi = "AT+CWMODE=1";

void NetInit(boolean keys) {
  //-----------------------------------------------------------------------
  key = keys;
  //-----------------------------------------------------------------------
  ATSend(testAT, "OK", "", 10, key); loopSerial1(key); delay(1000);
  ATSend(jionAP, "OK", "", 10, key); loopSerial1(key); delay(2000);
  ATSend(seesAP, "OK", "", 10, key); loopSerial1(key); delay(1000);
  ATSend(seesIP, "OK", "", 10, key); loopSerial1(key); delay(1000);
  //-----------------------------------------------------------------------
  //ATSend(toWiFi,  "OK", "no change",10,key); loopSerial1();delay(1000);
  //ATSend(reStar,"ready","invalid",  20,key); loopSerial1();delay(1000);
  //-----------------------------------------------------------------------
}


void NetATStart(boolean keys) {
  //-----------------------------------------------------------------------
  key = keys;
  //-----------------------------------------------------------------------
  ATSend(testAT, "OK", "", 10, key); loopSerial1(key); delay(1000);
  ATSend(seesAP, "OK", "", 10, key); loopSerial1(key); delay(1000);
  ATSend(seesIP, "OK", "", 10, key); loopSerial1(key); delay(1000);
  //-----------------------------------------------------------------------
}


void ATSend( String cmd, String backA, String backB, int TimeOutSecond, boolean backKey) {
  SoftSerialPrintln(cmd);
  if (backA.length() > 0) NetWaitBack(backA, backB, TimeOutSecond, backKey);
}

long wTime = millis();
long wTimeKey = 10 * 1000;
String NetWaitBack(String strA, String strB, int TimeOutSecond, boolean backKey) {
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
      if(backKey)SerialPrint(a);
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
      if (backKey) SerialPrintln("timeout");
      break;
    }
    //-----------------------------------
  }
  //------------------------------------------------
  return "";
  //------------------------------------------------
}

boolean DataIndexOf(String d, String s, boolean backKey) {
  //------------------------------------------------
  if (d.indexOf(s) != -1)
  {
    if(backKey){SerialPrint('=');SerialPrintln(s);}
    return true;
  } else {
    return false;
  }
  //------------------------------------------------
}

void NetSend(String x) {
  int n = x.length() + 2;
  String s = String("AT+CIPSEND=") + String(n);
  ATSend(s, ">", "", 20, key);
  ATSend(x, "SEND OK", "", 20, key);
}

void loopSerial1(boolean backKey) {
  while (SoftSerialAvailable() > 0) {
    char a = SoftSerialRead();
    if(backKey)SerialPrint(a);
  }
}
