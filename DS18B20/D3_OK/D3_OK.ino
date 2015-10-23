#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 //PIN 2
#define TEMPERATURE_PRECISION 12

OneWire onewire(ONE_WIRE_BUS);
DallasTemperature ds(&onewire);

int numberOfDevices;
DeviceAddress tempDeviceAddress;

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
    if (ds.getAddress(tempDeviceAddress, i))
    {
      ds.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
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
    if (ds.getAddress(tempDeviceAddress, i))
    {
      float tempC = ds.getTempC(tempDeviceAddress);
      Serial.print(tempC);
      Serial.print(" ");
    }
  }
  //--------------------------------------------
  Serial.println("");
  delay(5000);
  //--------------------------------------------
}

