#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.boboking.com";
IPAddress ip(192,168,1,177);
EthernetClient client;

 #include <OneWire.h>
#include <EtherCard.h>
#include <DallasTemperature.h>
#define OUT
// Data wire is plugged into port A5 on the Arduino
#define ONE_WIRE_BUS 7
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
 
#define REQUEST_RATE 15000 // milliseconds
// ethernet interface mac address 需要根据你的实际网络环境进行更改，我这儿用的是固定ip
static byte mymac[] = { 
  0x74,0x69,0x69,0x2D,0x30,0x31 };
// ethernet interface ip address
static byte myip[] = { 
  10,21,0,193 };
// gateway ip address
static byte gwip[] = { 
  10,21,0,1 };
// remote dns ip address
static byte dnsip[] = {
  10,21,0,1 };
 
// remote website name
char website[] PROGMEM = "www.lewei50.com";
char urlBuf[] PROGMEM = "/api/V1/gateway/UpdateSensors/01"; // 01应该更改为你对应的网关标识
char apiKey[] PROGMEM = "userkey:xxxxxxxxxxxxxxxxxxxxxxxxx"; //需要更改为你的userkey
byte Ethernet::buffer[700];   // a very small tcp/ip buffer is enough here
static long timer;
 
// called when the client request is complete
static void my_result_cb (byte status, word off, word len) {
  Serial.print("<<< reply ");
  Serial.print(millis() - timer);
  Serial.println(" ms");
  Serial.println((const char*) Ethernet::buffer + off);
}
 
void setup () {
  sensors.begin();
  Serial.begin(57600);
  Serial.println("\n[getStaticIP]");
 
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println( "Failed to access Ethernet controller");
 
  ether.staticSetup(myip, gwip, dnsip);
 
  while (ether.clientWaitingGw())
    ether.packetLoop(ether.packetReceive());
  Serial.println("Gateway found");
 
  timer = - REQUEST_RATE; // start timing out right away
}
 
void loop () {
  ether.packetLoop(ether.packetReceive());
 
  if (millis() > timer + REQUEST_RATE) {
    timer = millis();
    Serial.println("\n>>> REQ");
    static char buf[20];
    get_send_string(buf);
    if (!ether.dnsLookup(website))
      Serial.println("DNS failed");
    ether.printIp("Server: ", ether.hisip);
    ether.httpPost (urlBuf, website, apiKey, buf, my_result_cb);
  }
}
 
void get_send_string(OUT char *p){
  sensors.requestTemperatures();  
  uint16_t Tc_100 = sensors.getTempCByIndex(0)*10;
  uint8_t whole, fract;
  whole = Tc_100/10 ;  // separate off the whole and fractional portions
  fract = Tc_100 % 10;
  sprintf(p,"[{\"Name\":\"T2\",\"Value\":\"%d.%d\"}]",whole,fract);  //T2应该更改为你对应的设备标识
}
