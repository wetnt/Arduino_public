//=========================================
void EchoSerialPrintln(String cmd) {
  //Serial.print(cmd);
  //Serial.println("");
}
void EchoSerialPrint(char c) {
  //Serial.print(c);
}
//=========================================
void WorkSerialPrintln(String cmd) {
  //Serial1.println(cmd);
  Serial.println(cmd);
}
boolean WorkSerialAvailable() {
  //return Serial1.available() > 0;
  return Serial.available() > 0;
}
char WorkSerialRead() {
  //return Serial1.read();
  return Serial.read();
}
//=========================================
