//===============================================
#include <OneWire.h>
#include <DallasTemperature.h>
//--------------------------------------------
#define NOMBER_DS 8
#define ONE_WIRE_BUS 2 //PIN 2
#define TEMPERATURE_PRECISION 12
//--------------------------------------------
OneWire onewire(ONE_WIRE_BUS);
DallasTemperature ds(&onewire);
DeviceAddress dr[NOMBER_DS];
int dn = NOMBER_DS;
float dt[NOMBER_DS];
//===============================================
void DS18B20_setup()
{
  //--------------------------------------------
  ds.begin();
  dn = ds.getDeviceCount();
  for (int i = 0; i < dn; i++)
  {
    if (ds.getAddress(dr[i], i))
    {
      ds.setResolution(dr[i], TEMPERATURE_PRECISION);
    }
  }
  //--------------------------------------------
}
void DS18B20_setup_print()
{
  //--------------------------------------------
  Serial.print("Found ");
  Serial.print(dn, DEC);
  Serial.print(" devices.");
  Serial.println("");
  //--------------------------------------------
}
void DS18B20_loop()
{
  //--------------------------------------------
  ds.requestTemperatures();
  //--------------------------------------------
  for (int i = 0; i < dn; i++)
  {
    dt[i] = ds.getTempC(dr[i]);
  }
  //--------------------------------------------
  if ( dt[0] > 30 ||  dt[1] > 30 ||  dt[2] > 30 ||  dt[3] > 30 )
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  //--------------------------------------------
}
void DS18B20_loop_print()
{
  //--------------------------------------------
  for (int i = 0; i < dn; i++)
  {
    Serial.print(dt[i]); Serial.print(" ");
  }
  Serial.println("");
  //--------------------------------------------
}
//===============================================
boolean DS18B20_Min_Key(int key) {
  for (int i = 0; i < dn; i++) {
    if (dt[i] > key) return true;
  }
  return false;
}
boolean DS18B20_Max_Key(int key) {
  for (int i = 0; i < dn; i++)
  {
    if (dt[i] < key) return true;
  }
  return false;
}
//===============================================


void DS18B20_loop_print2()
{
  //--------------------------------------------
  Serial.print(dt[0]); Serial.print(",");
  Serial.print(dt[1]); Serial.print(",");
  Serial.print(dt[2]); Serial.println("");
  //--------------------------------------------
}
