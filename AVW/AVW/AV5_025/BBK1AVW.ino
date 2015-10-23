//===============================================================
#include <SoftwareSerial.h>
SoftwareSerial myAvw(A5,A3);//RX,TX
long AVWTime = millis(), AVWTimeKey = 1000;
//===============================================================
int   Volt = 10,Watt = 20;
float Amps = 0.1,Kwhs = 40.5,Pfss = 1,Cabn = 1;
//===============================================================
int retval,data[10],tt[30];  //int changed to unsigned int
//===============================================================
void AVW_Setup(){
  Serial.print("AVW_Setup......");
  myAvw.begin(4800);
  delay(2000);
  Serial.println("OK!");
}
//===============================================================
void AVW_Loop(bool showkey) {
  //------------------------------------------------------------- 
  if( millis() - AVWTime < AVWTimeKey) return; 
  AVWTime = millis();
  //------------------------------------------------------------- 
  Serial.print("AVW_Read_ON.....");
  retval = read_holding_registers(1, 0x49, 6, tt, 1);
  Serial.println("OFF");
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
  if(showkey){
    Serial.print("Volt = ");Serial.println(Volt);
    Serial.print("Amps = ");Serial.println(Amps);
    Serial.print("Watt = ");Serial.println(Watt);
    Serial.print("Kwhs = ");Serial.println(Kwhs);
    Serial.print("Pfss = ");Serial.println(Pfss);
    Serial.print("Cabn = ");Serial.println(Cabn);
  }
  //------------------------------------------------------------- 
}
//===============================================================

