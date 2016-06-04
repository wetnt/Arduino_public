//==============================================================================
struct MyBtType {
  char Types;
  long Times;
  int Level;
  void set(char s, long t,  int l) {
    Types = s; Times = t; Level = l;
  }
  void show(int address) {
    lg(address); lg(":\t"); lg(Types); lg(",\t"); lg(Times); lg(",\t"); lg( Level ); lg();
    ss.print(address); ss.print(":\t"); ss.print(Types); ss.print(",\t"); ss.print(Times); ss.print(",\t"); ss.print( Level ); ss.println();
  }
};
//==============================================================================
void EEPROM_setup() {
  Gets_Now_Address();
}
//==============================================================================
int nowAddress = 1;
void Gets_Now_Address() {
  nowAddress = EEPROM.read(0); Fmt_Now_Address();
}
void Save_Now_Address() {
  Fmt_Now_Address(); EEPROM.update(0, nowAddress);
}
void Fmt_Now_Address() {
  if (nowAddress == 0) nowAddress = 1;
  if (nowAddress + sizeof(MyBtType) > EEPROM.length()) nowAddress = 1;
}
//==============================================================================
void Puts_New_Data(char s, long t, int l) {
  MyBtType d; d.set(s, t, l); EEPROM.put( nowAddress, d );
  //MyBtType k; EEPROM.get(nowAddress, k); k.show(nowAddress);
  nowAddress += sizeof(MyBtType); Save_Now_Address();
}
void Get_All_Data() {
  int i = 1;
  while (i < EEPROM.length()) {
    MyBtType d; EEPROM.get(i, d);
    //if (d.Times <= 0) break;
    d.show(i);
    i += sizeof(MyBtType);
  }
}
void Set_New_Data() {
  rom_clear(); nowAddress = 1;
  EEPROM.update(0, nowAddress);
}
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
