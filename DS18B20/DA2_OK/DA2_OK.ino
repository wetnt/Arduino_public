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
//--------------------------------------------
void setup(void)
{
  //--------------------------------------------
  Serial.begin(115200);
  pinMode(13, OUTPUT);
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
  Serial.print("Found ");
  Serial.print(dn, DEC);
  Serial.print(" devices.");
  Serial.println("");
  //--------------------------------------------
}


void loop(void)
{
  //--------------------------------------------
  ds.requestTemperatures();
  //--------------------------------------------
  for (int i = 0; i < dn; i++)
  {
    dt[i] = ds.getTempC(dr[i]);
  }
  //--------------------------------------------
  for (int i = 0; i < dn; i++)
  {
    Serial.print(dt[i]); Serial.print(" ");
  }
  Serial.println("");
  delay(5000);
  //--------------------------------------------
  if ( dt[0] > 30 ||  dt[1] > 30 ||  dt[2] > 30 ||  dt[3] > 30 )
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  //--------------------------------------------
}

