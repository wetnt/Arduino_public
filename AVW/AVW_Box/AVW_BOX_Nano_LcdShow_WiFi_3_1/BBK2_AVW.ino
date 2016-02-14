//===============================================================
#include <SoftwareSerial.h>
static const long AvwBaud = 4800;
SoftwareSerial myAvw(10, 11); //RX,TX
//===============================================================
long AVWTime = millis(), AVWTimeKey = 1000;
//===============================================================
int   Volt = 0, Watt = 0;//电压,功率
float Amps = 0, Kwhs = 0;//电流,电量
float Pfss = 0, Cabn = 0;//功率因子,碳排放
//===============================================================
int retval, data[10], tt[30];
//===============================================================
void AVW_Setup() {
  myAvw.begin(AvwBaud); delay(1000);
  lg(F("AVW.Serial.start! = "));lg(AvwBaud);lg();
}
void AVW_Loop() {
  //-------------------------------------------------------------
  if ( millis() - AVWTime < AVWTimeKey) return;
  AVWTime = millis();
  //-------------------------------------------------------------
  lgln(F("AVW_Loop"));
  retval = read_holding_registers(1, 0x49, 6, tt, 1);
  //-------------------------------------------------------------
  Volt = tt[0]; Volt = Volt / 100;
  Amps = tt[1]; Amps = Amps / 1000;
  Watt = tt[2];
  unsigned int  Kwhh = (unsigned int)tt[3];
  unsigned int  Kwhl = (unsigned int)tt[4];
  unsigned long kwhA = (unsigned long) Kwhh * 65536 + Kwhl;
  Kwhs = kwhA; Kwhs = Kwhs / 3200;
  Pfss = tt[5]; Pfss = Pfss / 1000;
  Cabn = tt[5]; Cabn = Cabn / 1000;
  //-------------------------------------------------------------
  //AVW_Show();
  //-------------------------------------------------------------
}
//===============================================================
void AVW_Show() {
  //-------------------------------------------------------------
  lg(F("----------------")); lg();
  lg(F("Volt = ")); lg(Volt); lg();
  lg(F("Amps = ")); lg(Amps); lg();
  lg(F("Watt = ")); lg(Watt); lg();
  lg(F("Kwhs = ")); lg(Kwhs); lg();
  lg(F("Pfss = ")); lg(Pfss); lg();
  lg(F("Cabn = ")); lg(Cabn); lg();
  //-------------------------------------------------------------
}
//===============================================================

