#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//------------------------------------------
//char ssid[] = "MMMM";
//char pass[] = "1234567890123";
//------------------------------------------
char ssid[] = "jtwx4.1";
char pass[] = "jtwx1234";
//------------------------------------------
WiFiUDP udp;
//------------------------------------------
void wifi_setup() {
  wifi_addAP();
  udp_setup();
}
void wifi_addAP() {
  lg("Connecting to "); lg(ssid); lg();
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500); lg(".");
  }
  lg();

  lg("WiFi connected IP address: ");
  lg(WiFi.localIP()); lg();
}
void udp_setup() {
  udp.begin(localPort);
  lg("Starting UDP Local port: ");
  lg(udp.localPort());
  lg();
}
void wifi_loop() {
  WiFi.hostByName(ntpServerName, timeServerIP);
  NTPpacket();
  udp_loop(timeServerIP, NTP_Port);
  
  int cb = udp.parsePacket();
  if (!cb) {
    lg("no packet yet"); lg();
  } else {
    //lg("packet received, length = "); lg(cb); lg();
    udp.read(packetBuffer, NTP_PACKET_SIZE);
    unsigned long Unix_time = getsNTPTime();
    TimeSet(Unix_time);
  }
}

void udp_loop(IPAddress& address, int ntp_port) {
  udp.beginPacket(address, ntp_port); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

