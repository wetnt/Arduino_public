#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 //PIN 2
#define TEMPERATURE_PRECISION 12

OneWire onewire(ONE_WIRE_BUS);
DallasTemperature ds(&onewire);

int numberOfDevices;
DeviceAddress drs[4];

float t[4];

void setup(void)
{
  //--------------------------------------------
  Serial.begin(115200);
  //--------------------------------------------
  ds.begin();
  numberOfDevices = ds.getDeviceCount();
  //--------------------------------------------
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");
  //--------------------------------------------
  Serial.print("Parasite power is: ");
  if (ds.isParasitePowerMode())
    Serial.println("ON");
  else
    Serial.println("OFF");
  //--------------------------------------------
  for (int i = 0; i < numberOfDevices; i++)
  {
    if (ds.getAddress(drs[i], i))
    {
      ds.setResolution(drs[i], TEMPERATURE_PRECISION);
    }
  }
  //--------------------------------------------
}


void loop(void)
{
  //--------------------------------------------
  ds.requestTemperatures();
  //--------------------------------------------
  for (int i = 0; i < numberOfDevices; i++)
  {
    t[i] = ds.getTempC(drs[i]);
  }
  //--------------------------------------------
  Serial.print(t[0]);Serial.print(" ");
  Serial.print(t[1]);Serial.print(" ");
  Serial.print(t[2]);Serial.print(" ");
  Serial.print(t[3]);Serial.print(" ");
  Serial.println("");
  delay(5000);
  //--------------------------------------------
}

