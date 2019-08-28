/*
    This sketch trys to Connect to the best AP based on a given list

*/
#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;
String SSID_Now = "----";
String RSSI_Now = "----";

void setup()
{
  M5.begin();
  Serial.begin(115200);
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);

  delay(10);

  wifiMulti.addAP("JTFY", "jtfy2468");
  wifiMulti.addAP("MMMM", "1234567890123");
  wifiMulti.addAP("kzn701", "zhouziheng");

  Serial.println("Connecting Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("IP address: ");
    Serial.println(WiFi.SSID().c_str());
    Serial.println(WiFi.psk().c_str());
  }

  SSID_Now = String(WiFi.SSID().c_str());
  RSSI_Now = String(WiFi.RSSI());

  Serial.print(SSID_Now);
  Serial.print(" ");
  Serial.println(WiFi.RSSI());

  WiFi_scan();
}

void WiFi_scan()
{
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");Serial.print(WiFi.SSID(i));
      Serial.print(" (");Serial.print(WiFi.RSSI(i));Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}

void loop()
{

  if (digitalRead(M5_BUTTON_RST) == LOW) {
    delay(200);
    esp_restart();
  }



  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  } else {

    SSID_Now = String(WiFi.SSID().c_str());
    RSSI_Now = String(WiFi.RSSI());

    Serial.print(SSID_Now);
    Serial.print(" ");
    Serial.println(WiFi.RSSI());

    M5.Lcd.setRotation(3);
    //--------------------------------------------------
    M5.Rtc.GetBm8563Time(); RTC_DateTypeDef RTC_DateStruct; M5.Rtc.GetData(&RTC_DateStruct);
    //--------------------------------------------------
    M5.Lcd.setCursor(  0,  0, 2);  M5.Lcd.printf("%04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
    M5.Lcd.setCursor( 82,  0, 2);  M5.Lcd.print(SSID_Now);
    M5.Lcd.setCursor(122,  0, 2);  M5.Lcd.print(RSSI_Now);
    //--------------------------------------------------
    M5.Lcd.setCursor( 20, 24, 4);  M5.Lcd.printf("%02d:%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
    //--------------------------------------------------







    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("IP address: ");
    Serial.println(WiFi.SSID().c_str());
    Serial.println(WiFi.psk().c_str());
    Serial.println(WiFi.RSSI());
    //Serial.println(WiFi.BSSID().c_str());
    //Serial.println(String(WiFi.BSSID("JTFY")));

    //int32_t RSSI()
    delay(2000);
  }
}
