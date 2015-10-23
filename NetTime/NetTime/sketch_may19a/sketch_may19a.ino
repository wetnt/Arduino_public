// // ESP8266 connection

/* Connect ESP8266 as follows
  I used an Arduino 3.3v Pro Mini with a 3.3V USB-FTDI converter
  The ESP8266 was communicating at 9600 when delivered
  Vcc - 3.3v
  gnd - gnd
  rx - pin 11
  tx - pin 10
  ch_PD - pin 6
*/

// Target Access Point
#define ssid         "MMMM"
#define pass         "1234567890123"

int EnablePin = 6;
unsigned long time = 0;

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX


void setup()
{

  pinMode(EnablePin, OUTPUT);
  digitalWrite(EnablePin, LOW);
  delay (500);
  digitalWrite(EnablePin, HIGH);
  delay (500);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay (1000);

  connectWiFi();  // Start the WiFi module

  setPacket();

}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}

void connectWiFi()
{

  //Rest the module.
  Serial.println("AT+RST");
  mySerial.println("AT+RST");
  time = millis();
  while ((time + 2000) >= millis()) {
    if (mySerial.available() > 0) {
      Serial.write(mySerial.read());
    }
  }

  delay(20);

  //Set the wireless mode
  Serial.println("AT+CWMODE=1");
  mySerial.println("AT+CWMODE=1");
  time = millis();
  while ((time + 500) >= millis()) {
    if (mySerial.available() > 0) {
      Serial.write(mySerial.read());
    }
  }
  delay(20);

  //disconnect  - it shouldn't be but just to make sure
  Serial.println("AT+CWQAP");
  mySerial.println("AT+CWQAP");
  time = millis();
  while ((time + 1000) >= millis()) {
    if (mySerial.available() > 0) {
      Serial.write(mySerial.read());
    }
  }

  // connect to your wireless router
  String cmd = "AT+CWJAP=\"";
  cmd += ssid;
  cmd += "\",\"";
  cmd += pass;
  cmd += "\"";
  Serial.println(cmd);
  mySerial.println(cmd);
  //delay(2000);
  time = millis();
  while ((time + 15000) >= millis()) {
    if (mySerial.available() > 0) {
      Serial.write(mySerial.read());
    }
  }

  //print the ip addr
  mySerial.println("AT+CIFSR");
  Serial.println("ip address:");
  time = millis();
  while ((time + 5000) >= millis()) {
    if (mySerial.available() > 0) {
      Serial.write(mySerial.read());
    }
  }

  //set the single connection mode
  Serial.println("AT+CIPMUX=0");
  mySerial.println("AT+CIPMUX=0");
  time = millis();
  while ((time + 1000) >= millis()) {
    if (mySerial.available() > 0) {
      Serial.write(mySerial.read());
    }
  }

  //Connect to the NTP server

  String cmd1 = "AT+CIPSTART=\"UDP\",\"";
  cmd1 += "129.6.15.28";
  cmd1 += "\",123";
  mySerial.println(cmd1);
  Serial.println(cmd1);
  time = millis();
  while ((time + 5000) >= millis()) {
    if (mySerial.available() > 0) {
      Serial.write(mySerial.read());
    }
  }
}

void setPacket() {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  //mySerial.write("192.168.0.13", 123);
  mySerial.write(packetBuffer, NTP_PACKET_SIZE);
  // Serial.println(packetBuffer,NTP_PACKET_SIZE);
  //Udp.endPacket();
}
