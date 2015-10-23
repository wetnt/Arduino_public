#include <Adafruit_ESP8266.h>
#include <SoftwareSerial.h>

#define ESP_RX   2
#define ESP_TX   3
#define ESP_RST  4
SoftwareSerial softser(ESP_RX, ESP_TX);
Adafruit_ESP8266 wifi(&softser, &Serial, ESP_RST);

#define ESP_SSID "MMMM" // Your network name here
#define ESP_PASS "1234567890123" // Your network password here

#define HOST     "www.adafruit.com"     // Host to contact
#define PAGE     "/testwifi/index.html" // Web page to request
#define PORT     80                     // 80 = HTTP default port

#define LED_PIN  13

void setup() {
  char buffer[50];

  // Flash LED on power-up
  pinMode(LED_PIN, OUTPUT);
  for(uint8_t i=0; i<3; i++) {
    digitalWrite(13, HIGH); delay(50);
    digitalWrite(13, LOW);  delay(100);
  }

 wifi.setBootMarker(F("Version:0.9.2.4]\r\n\r\nready"));

  softser.begin(9600); // Soft serial connection to ESP8266
  Serial.begin(57600); while(!Serial); // UART serial debug

  Serial.println(F("Adafruit ESP8266 Demo"));

  // Test if module is ready
  Serial.print(F("Hard reset..."));
  if(!wifi.hardReset()) {
    Serial.println(F("no response from module."));
    for(;;);
  }
  Serial.println(F("OK."));

  Serial.print(F("Soft reset..."));
  if(!wifi.softReset()) {
    Serial.println(F("no response from module."));
    for(;;);
  }
  Serial.println(F("OK."));

  Serial.print(F("Checking firmware version..."));
  wifi.println(F("AT+GMR"));
  if(wifi.readLine(buffer, sizeof(buffer))) {
    Serial.println(buffer);
    wifi.find(); // Discard the 'OK' that follows
  } else {
    Serial.println(F("error"));
  }

  Serial.print(F("Connecting to WiFi..."));
  if(wifi.connectToAP(F(ESP_SSID), F(ESP_PASS))) {

    // IP addr check isn't part of library yet, but
    // we can manually request and place in a string.
    Serial.print(F("OK\nChecking IP addr..."));
    wifi.println(F("AT+CIFSR"));
    if(wifi.readLine(buffer, sizeof(buffer))) {
      Serial.println(buffer);
      wifi.find(); // Discard the 'OK' that follows

      Serial.print(F("Connecting to host..."));
      if(wifi.connectTCP(F(HOST), PORT)) {
        Serial.print(F("OK\nRequesting page..."));
        if(wifi.requestURL(F(PAGE))) {
          Serial.println("OK\nSearching for string...");
          // Search for a phrase in the open stream.
          // Must be a flash-resident string (F()).
          if(wifi.find(F("working"), true)) {
            Serial.println(F("found!"));
          } else {
            Serial.println(F("not found."));
          }
        } else { // URL request failed
          Serial.println(F("error"));
        }
        wifi.closeTCP();
      } else { // TCP connect failed
        Serial.println(F("D'oh!"));
      }
    } else { // IP addr check failed
      Serial.println(F("error"));
    }
    wifi.closeAP();
  } else { // WiFi connection failed
    Serial.println(F("FAIL"));
  }
}

void loop() {
}
