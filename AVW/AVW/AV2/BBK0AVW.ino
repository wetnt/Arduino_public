//===============================================================
int   Volt = 0;
float Amps = 0;
int   Watt = 0;
float Kwhs = 0;
float Pfss = 0;
float Cabn = 0;
//===============================================================
void AVWInit(){
  myAvw.begin(4800);
  delay(2000);
}
//===============================================================
int retval;
int data[10];
int tt[30];  //int changed to unsigned int
//===============================================================
long AVWTime = millis(), AVWTimeKey = 5000;//5s
void AVWRead() {
  //------------------------------------------------------------- 
  if( millis() - AVWTime < AVWTimeKey) return; 
  AVWTime = millis();
  //------------------------------------------------------------- 
  retval = read_holding_registers(1, 0x49, 6, tt, 1);
  //------------------------------------------------------------- 
  Volt = tt[0]; Volt = Volt / 100;
  Amps = tt[1]; Amps = Amps / 1000;
  Watt = tt[2];
  unsigned int  Kwhh = (unsigned int)tt[3];
  unsigned int  Kwhl = (unsigned int)tt[4];
  unsigned long kwhA = (unsigned long) Kwhh *65536 + Kwhl;
  Kwhs = kwhA;  Kwhs = Kwhs / 3200;
  Pfss = tt[5]; Pfss = Pfss / 1000;
  Cabn = tt[5]; Cabn = Cabn / 1000;
  //------------------------------------------------------------- 
}
//===============================================================
