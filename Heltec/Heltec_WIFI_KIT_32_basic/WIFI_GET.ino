
int value = 0;
const char* host = "www.bbkgps.com";
const int   httpPort = 80;

void sdf() {
  ++value;
  Serial.print("connecting to "); Serial.println(host);

  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    wifi_add_new();
    return;
  }

//  IPAddress host_Address;
//  WiFi.hostByName(host, host_Address);
//  Serial.print("host_Address: "); Serial.println(host_Address);

  String url = "/w.php";
  url += "?value=";
  url += value;

  Serial.print("Requesting URL: "); Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();

  while (client.available() == 0) {
    if (millis() - timeout > 10000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  String getBack = "";
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
    getBack += line;
  }
  Serial.println();
  Serial.println("closing connection");

  oled_str(getBack);
}

