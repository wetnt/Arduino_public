
//------------------------------------------------------
//int SerialKey = 1;//0false/1true/2wait/4timeout
String SerialData = "";
boolean SerialBackKey = true;
//------------------------------------------------------
boolean SerialLoopKey = false;
long SerialTimes = millis();
long SerialTimeK = 10 * 1000;
String SerA = ""; String SerB = ""; String SerialStr = "";
//------------------------------------------------------
void SerialWaitSet(String a, String b, int TimeOutSecond, boolean key) {
  //------------------------------------------------
  SerialStr = ""; SerialData = "";
  //------------------------------------------------
  SerA = a; SerB = b;
  SerialBackKey = key;
  //------------------------------------------------
  SerialTimes = millis();
  SerialTimeK = TimeOutSecond * 1000;
  SerialLoopKey = true;
  //------------------------------------------------
}
String SerialWaitBack() {
  return SerialData;
}
//------------------------------------------------------
//------------------------------------------------------
//------------------------------------------------------
void SerialWaitLoop() {
  //------------------------------------------------
  if (!SerialLoopKey)return;
  //------------------------------------------------
  if (WorkSerialAvailable()) {
    char a = WorkSerialRead();
    SerialStr = SerialStr + a;
    if (SerialBackKey)
      EchoSerialPrint(a);
  }
  //------------------------------------------------
  if (DataIndexOf(SerialStr, "busy")  ) {
    SerialNextClear(2);
    SerialLoopKey = true;
    return;
  }
  if (DataIndexOf(SerialStr, "ERROR") ) {
    SerialNextClear(0);
    return;
  }
  if (SerB.length() <= 0) {
    if (DataIndexOf(SerialStr, SerA)  ) {
      SerialNextClear(1);
      return;
    }
  } else {
    if (DataIndexOf(SerialStr, SerA)  ) {
      SerialNextClear(2);
      SerialLoopKey = true;
      return;
    }
    if (DataIndexOf(SerialStr, SerB)  ) {
      SerialData = String(SerialStr);
      SerialNextClear(5);
      SerialLoopKey = true;
      return;
    }
  }
  //------------------------------------------------
  if ( millis() - SerialTimes > SerialTimeK ) {
    SerialTimes = millis();
    SerialNext(4);
    return;
  }
  //------------------------------------------------
}
void SerialNextClear(int key) {
  SerialLoopKey = false;
  SerialStr = "";
  SerialNext(key);
}
//------------------------------------------------------
//------------------------------------------------------
