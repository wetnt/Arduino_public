//===============================================================
#include <SoftwareSerial.h>
static const long AvwBaud = 4800;
SoftwareSerial myAvw(10, 11); //RX,TX
//===============================================================
long AVWTime = millis(), AVWTimeKey = 2000;
//===============================================================
int   Volt = 0, Watt = 0;//电压,功率
float Amps = 0, Kwhs = 0;//电流,电量
float Pfss = 0, Cabn = 0;//功率因子,碳排放
//===============================================================
unsigned char query[] = {0x01, 0x03, 0x00, 0x48, 0x00, 0x06, 0x45, 0xDE};
unsigned char AvwBuf[20];
//unsigned char AvwBuf[] = {
//  0x5C, 0xBB, //电压3,4
//  0x00, 0x00, //电流5,6
//  0x00, 0x00, //功率7,8
//  0x00, 0x5A, //电量9,10,high
//  0xA1, 0xA0, //电量11,12,low
//  0x00, 0x00, //功率因子13,14
//};
//===============================================================
void AVW_Setup() {
  myAvw.begin(AvwBaud); delay(1000);
  lgln(F("AVW.Serial.start!"));
}
void AVW_Loop() {
  //-------------------------------------------------------------
  if ( millis() - AVWTime < AVWTimeKey) return;
  AVWTime = millis();
  //-------------------------------------------------------------
  BufferClear(); myAvw_Ask(); smartDelay(2000);
  AVW_Exp(); AVW_Show();
  //-------------------------------------------------------------
}
//===============================================================
void myAvw_Ask() {
  for (int i = 0; i < 8; i++) myAvw.write(query[i]);
}
//===============================================================
int BufferIndex = -1;
int BufferLength = 20;
void BufferClear() {
  BufferIndex = -1;
  for (int i = 0; i < BufferLength; i++) AvwBuf[i] = '\0';
}
void BufferSave(char c) {
  BufferIndex++;
  AvwBuf[BufferIndex] = c;
}
void myAvw_loop() {
  while (myAvw.available()) {
    char c = myAvw.read();
    BufferSave(c);
    //lgs.print(c, HEX); lg(' ');
  }
}
//===============================================================
void AVW_Exp() {
  //-------------------------------------------------------------
  Volt = AvwBuf[3] * 256 + AvwBuf[4]; Volt = Volt / 100;
  Amps = AvwBuf[5] * 256 + AvwBuf[6]; Amps = Amps / 1000;
  Watt = AvwBuf[7] * 256 + AvwBuf[8];
  unsigned int  Kwhh = (unsigned long)AvwBuf[9] * 256 + (unsigned long)AvwBuf[10];
  unsigned int  Kwhl = (unsigned long)AvwBuf[11] * 256 + (unsigned long)AvwBuf[12];
  unsigned long kwhA = Kwhh * 65536 + Kwhl; Kwhs = kwhA; Kwhs = Kwhs / 3200;
  Pfss = AvwBuf[13] * 256 + AvwBuf[14]; Pfss = Pfss / 1000;
  //-------------------------------------------------------------
}
void AVW_Show() {
  //-------------------------------------------------------------
  //lg(F("----------------")); lg();
  lg(F("Volt = ")); lg(Volt); lg('\t');
  lg(F("Amps = ")); lg(Amps); lg('\t');
  lg(F("Watt = ")); lg(Watt); lg('\t');
  lg(F("Kwhs = ")); lg(Kwhs); lg('\t');
  lg(F("Pfss = ")); lg(Pfss); lg('\t');
  lg(F("Cabn = ")); lg(Cabn); lg();
  //-------------------------------------------------------------
}
//===============================================================

