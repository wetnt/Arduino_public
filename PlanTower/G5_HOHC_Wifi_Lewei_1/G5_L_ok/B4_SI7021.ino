#include <Wire.h>
#include <Si7021.h>
Si7021 Si;
float Si_Temperature, Si_Humidity;
void Si7021_setup() {
  lgln(F("Si7021_setup..."));
  Wire.begin();
  if (Si.detectSensor())
    lgln(F("Device detected"));
  else
    lgln(F("Device NOT detected"));
}
void Si7021_read() {
  Si_Temperature = Si.getTemperature();
  Si_Humidity = Si.getHumidity();
}
void Si7021_show() {
  lg("Temperature: "); lg(Si_Temperature); lg(" C, Humidity: "); lg(Si_Humidity); lg(" %"); lg();
}

