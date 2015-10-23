//===============================================================
int   Volt = 0,Watt = 0;
float Amps = 0,Kwhs = 0,Pfss = 0,Cabn = 0;
//===============================================================
long AVWTime = millis(), AVWTimeKey = 1000;//5s
//===============================================================
int retval,data[10],tt[30];  //int changed to unsigned int
//===============================================================
void AVW_Setup(){
  myAvw.begin(4800);
  delay(2000);
}
//===============================================================
void AVW_Loop() {
  //------------------------------------------------------------- 
  retval = read_holding_registers(1, 0x49, 6, tt, 1);
  //------------------------------------------------------------- 
  Volt = tt[0]; 
  Volt = Volt / 100;
  Amps = tt[1]; 
  Amps = Amps / 1000;
  Watt = tt[2];
  unsigned int  Kwhh = (unsigned int)tt[3];
  unsigned int  Kwhl = (unsigned int)tt[4];
  unsigned long kwhA = (unsigned long) Kwhh *65536 + Kwhl;
  Kwhs = kwhA;  
  Kwhs = Kwhs / 3200;
  Pfss = tt[5]; 
  Pfss = Pfss / 1000;
  Cabn = tt[5]; 
  Cabn = Cabn / 1000;
  //------------------------------------------------------------- 
}
//===============================================================

