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
      SerialPrintln("");
      SerialPrintln("=");
      SerialPrintln(s);
    }
    return true;
  } else {
    return false;
  }
  //------------------------------------------------
}

void NetSend(String x) {
  //------------------------------------------------
  int n = x.length() + 1;
  String s = String("AT+CIPSEND=0,") + String(n);
  ATSend(s, ">", "", 30, true); //delay(1000);
  ATSend(x, "SEND OK", "", 30, true);
  //------------------------------------------------
}
