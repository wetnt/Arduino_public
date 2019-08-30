//BMP280气压传感器
Adafruit_BMP280 bme;
float pressure;

void BMP280_setup() {
  if (!bme.begin(0x76)) {
    lcd_show("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  } else {
    lcd_show("BMP280 , ok!");
  }
}

void BMP280_loop() {
  pressure = bme.readPressure();
  Serial.printf("pressure: %2.1f", pressure);lg();
}
