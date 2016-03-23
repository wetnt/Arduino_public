#include <Wire.h>
#include <Si7021.h>
Si7021 Si;
void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("a");
  if (Si.detectSensor()) {
    Serial.println("Device detected");
  } else {
    Serial.println("Device NOT detected");
    while (1) {
      ;;
    }
  }
}

void loop() {
  float temperature, humidity;

  temperature = Si.getTemperature();
  humidity = Si.getHumidity();

  // And output the data
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %RH");
  delay(1000);
}
