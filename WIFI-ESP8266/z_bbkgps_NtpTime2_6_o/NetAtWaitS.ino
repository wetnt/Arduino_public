
//------------------------------------------------------
int SerialKey = 1;//0false/1true/2wait/4timeout
String SerialStr = "";
boolean SerialBackKey = true;
//------------------------------------------------------
long SerialTimes = millis();
long SerialTimeK = 10 * 1000;
String SerA = ""; String SerB = "";
//------------------------------------------------------
void SerialWaitSet(String a, String b, int TimeOutSecond, boolean key) {
  //------------------------------------------------
  SerA = a; SerB = b;
  SerialBackKey = key;
  SerialTimes = millis();
  SerialTimeK = TimeOutSecond * 1000;
  //------------------------------------------------
}
void SerialWaitBack() {
  //------------------------------------------------
  if (SoftSerialAvailable()) {
    char a = SoftSerialRead();
    SerialStr = SerialStr + a;
    if (SerialBackKey)SerialPrint(a);
  }
  //------------------------------------------------
  if (DataIndexOf(SerialStr, "busy")  ) {
    SerialNext(2);
    return;
  }
  if (DataIndexOf(SerialStr, "ERROR") ) {
    SerialNext(0);
    return;
  }
  if (SerB.length() <= 0) {
    if (DataIndexOf(SerialStr, SerA)  ) {
      SerialNext(1);
      return;
    }
  } else {
    if (DataIndexOf(SerialStr, SerA)  ) {
      SerialStr = "";
      SerialNext(2);
      return;
    }
    if (DataIndexOf(SerialStr, SerB)  ) {
      SerialNext(1);
      return;
    }
  }
  //------------------------------------------------
  if ( millis() - SerialTimes > SerialTimeK ) {
    SerialKey = 0;
    SerialNext(4);
    return;
  }
  //------------------------------------------------
}
//------------------------------------------------------
//void SerialNext() {
//}
//------------------------------------------------------
//------------------------------------------------------
