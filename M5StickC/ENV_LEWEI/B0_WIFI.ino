#include <WiFi.h>
#include <WiFiMulti.h>

const char* ssid       = "JTFY";
const char* password   = "jtfy2468";

WiFiMulti WiFiMulti;

void InitWifi()
{
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  int wn = 0;
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      wn++;if(wn%20==0){Serial.println("");}
  }
  Serial.println(" CONNECTED");

 // WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);
}

void wifi_test() {
    M5.Lcd.setTextColor(BLACK, WHITE);
    M5.Lcd.setCursor(7, 0, 2);
    M5.Lcd.println("WIFI TEST");
    
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    
    int n = WiFi.scanNetworks();
    M5.Lcd.setCursor(7, 20, 2);
    M5.Lcd.println("scan done");
  
  if (n == 0) {      M5.Lcd.setTextColor(RED, WHITE);
    } else    {      M5.Lcd.setTextColor(GREEN, WHITE);    }

    Serial.printf("%d AP", n);
}
