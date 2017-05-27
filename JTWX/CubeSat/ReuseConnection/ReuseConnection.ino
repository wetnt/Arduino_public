#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>


#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN D4

Adafruit_NeoMatrix matrix =
  Adafruit_NeoMatrix(8, 8, PIN,
                     NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                     NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                     NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(0, 0, 255),
  matrix.Color(0, 255, 0),
  matrix.Color(255,255, 0)
};



#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;
HTTPClient http;

void setup() {  

  USE_SERIAL.begin(115200);


  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 2; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);  

  //WiFiMulti.addAP("SSID", "PASSWORD");
  WiFiMulti.addAP("jtwx4.1", "jtwx1234");
  /*
        WiFiMulti.begin("jtwx4.1", "jtwx1234");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

  */

  USE_SERIAL.println(WiFi.localIP());
  // allow reuse (if server supports it)
  http.setReuse(true);
}

int x    = matrix.width();
int pass = 0;


void loop() {

  String txt = "COMMSAT12345$#@$&*:)";
  int n = (txt.length() + 1) * 6;

  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(txt);

  if (--x < -n) {
    x = matrix.width();

    if (++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }

  matrix.show();
  delay(100);

  


  
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    http.begin("http://www.bbkgps.com/");
    //http.begin("www.baidu.com", 80, "/");

    delay(5000);
    int httpCode = http.GET();

    USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);


    if (httpCode > 0) {
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        http.writeToStream(&USE_SERIAL);
      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(1000);
}



