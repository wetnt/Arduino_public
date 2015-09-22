//=========================================
void EchoSerialPrintln(String cmd) {
  Serial.print(cmd);
  Serial.println("");
}
void EchoSerialPrintln(int c) {
  Serial.print(c);
  Serial.println("");
}
void EchoSerialPrint(String cmd) {
  Serial.print(cmd);
}
void EchoSerialPrint(int c) {
  Serial.print(c);
}
void EchoSerialPrint(char c) {
  Serial.print(c);
}
//=========================================
void WorkSerialPrintln(String cmd) {
  Serial1.println(cmd);
  //Serial.println(cmd);
}
boolean WorkSerialAvailable() {
  return Serial1.available() > 0;
}
char WorkSerialRead() {
  return Serial1.read();
}
//=========================================
