//=========================================================================
typedef struct SmartSerial {
  //----------------------------------------------------------------
  bool backKey = true;
  //HardwareSerial *work;
  String errBreak[2] = {"busy", "ERROR"};
  //----------------------------------------------------------------
  //void SmartSerial(HardwareSerial *workPort, HardwareSerial *logShow, bool backKey) {
  // }
  //void init(HardwareSerial *workPort, HardwareSerial *logShow, bool backKey, String errBreaks) {
  //----------------------------------------------------------------
  void init(bool backKey) {
    //workPort = work;
    backKey = backKey;
  }
  //----------------------------------------------------------------
  String CmdSend(String cmd, String backA, String backB, int TimeOutSecond) {
    if (backKey)lg(cmd);
    gsm.println(cmd);
    if (backA.length() > 0) {
      return CmdWaitBack(backA, backB, TimeOutSecond);
    } else {
      return "noBackA";
    }
  }
  bool CmdSendOK(String cmd, int TimeOutSecond) {
    return CmdSend(cmd, "OK", "", TimeOutSecond) == "OK";
  }
  //----------------------------------------------------------------
  long wTime = millis();
  long wTimeKey = 20 * 1000;
  String CmdWaitBack(String strA, String strB, int TimeOutSecond) {
    //------------------------------------------------
    wTimeKey = TimeOutSecond * 1000;
    wTime = millis();
    //------------------------------------------------
    String data;
    while (1) {
      //-----------------------------------
      if (gsm.available()) {
        char a = gsm.read();
        data = data + a;
        //lgchar(a);
      }
      //-----------------------------------
      for (int i; i < 2; i++) {
        if (DataIndexOf(data, errBreak[i])) return "errBreak[i]";
      }
      //-----------------------------------
      if (strB.length() > 0) {
        if (DataIndexOf(data, strA)) data = "";
        if (DataIndexOf(data, strB)) return data;
      } else {
        if (DataIndexOf(data, strA)) return strA;
      }
      //-----------------------------------
      if (millis() - wTime > wTimeKey) {
        if (backKey) return "=timeout";
      }
      //-----------------------------------
      gpsLoop();
      //smartDelay(0);
      //-----------------------------------
    }
    //------------------------------------------------
    return "???";
    //------------------------------------------------
  }
  //----------------------------------------------------------------
  //----------------------------------------------------------------
};
bool DataIndexOf(String d, String s) {
  return (d.indexOf(s) != -1);
}
//=========================================================================

