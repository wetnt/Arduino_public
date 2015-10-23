#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 12

OneWire onewire(ONE_WIRE_BUS);
DallasTemperature ds(&onewire);

int numberOfDevices;
DeviceAddress tempDeviceAddress;

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");

  ds.begin();
  numberOfDevices = ds.getDeviceCount();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (ds.isParasitePowerMode())
    Serial.println("ON");
  else
    Serial.println("OFF");

  // Loop through each device, print out address
  for (int i = 0; i < numberOfDevices; i++)
  {
    // Search the wire for address
    if (ds.getAddress(tempDeviceAddress, i))
    {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();

      Serial.print("Setting resolution to ");
      Serial.println(TEMPERATURE_PRECISION, DEC);

      ds.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);

      Serial.print("Resolution actually set to: ");
      Serial.print(ds.getResolution(tempDeviceAddress), DEC);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }

}


void loop(void)
{
  ds.requestTemperatures();

  for (int i = 0; i < numberOfDevices; i++)
  {
    if (ds.getAddress(tempDeviceAddress, i))
    {
      Serial.print(i, DEC);
      Serial.print(" ");
      float tempC = ds.getTempC(tempDeviceAddress);
      Serial.print(tempC);
      Serial.println("");
    }
  }
  delay(10000);
  Serial.println(":");
  Serial.println(":");
  Serial.println(":");
}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
