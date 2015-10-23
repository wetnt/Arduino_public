#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


SoftwareSerial myAvw(10, 11);//RX,TX

int preset_multiple_registers(int slave, int start_addr, int reg_count, int *data);
int read_holding_registers(int slave, int start_addr, int count,int *dest, int dest_size);

void setup() {
  //--------------------------------------- 
  Serial.begin(115200);
  Serial.println("starttime");
  //--------------------------------------- 
  BBKLcdInit();
  AVWInit();
  //--------------------------------------- 
}

void loop() {
  //--------------------------------------- 
  AVWRead();
  //---------------------------------------  
  SerialShow();
  BBKLcdShow();
  //---------------------------------------  
  delay(1000);
  //---------------------------------------  
}
