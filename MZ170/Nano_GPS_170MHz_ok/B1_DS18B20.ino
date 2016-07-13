//===============================================
#include <OneWire.h>
#include <DallasTemperature.h>
//--------------------------------------------
#define NOMBER_DS 8
#define ONE_WIRE_BUS A0 //PIN A5
#define TEMPERATURE_PRECISION 12
//--------------------------------------------
OneWire onewire(ONE_WIRE_BUS);
DallasTemperature ds(&onewire);
DeviceAddress dr[NOMBER_DS];
int dn = NOMBER_DS;
float dt[NOMBER_DS];
//===============================================
void DS18B20_Init() {
  //--------------------------------------------
  lgln(F("DS18B20_Init..."));
  ds.begin(); dn = ds.getDeviceCount();
  //--------------------------------------------
  for (int i = 0; i < dn; i++)  {
    if (ds.getAddress(dr[i], i)) ds.setResolution(dr[i], TEMPERATURE_PRECISION);
  }
  //--------------------------------------------
  lg(F("Found ")); lg(dn); lg(F(" devices")); lg();
  //--------------------------------------------
}
void DS18B20_loop() {
  //--------------------------------------------
  ds.requestTemperatures();
  for (int i = 0; i < dn; i++) dt[i] = ds.getTempC(dr[i]);
  //--------------------------------------------
}
void DS18B20_print() {
  //--------------------------------------------
  for (int i = 0; i < dn; i++) {
    lg(dt[i]); lg(",");
  }
  lg();
  //--------------------------------------------
}
//===============================================
float GetMyCupTemperature() {
  return dt[0];
}
//===============================================
