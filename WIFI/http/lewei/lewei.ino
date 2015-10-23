    client.println("GET /!wap/ HTTP/1.1");
    client.println("Host: www.boboking.com");
    client.println("Connection: close");
	

	
	http://blog.csdn.net/liang890319/article/details/8575159
	http://www.arduino.cn/thread-3579-1-1.html
	http://blog.yeelink.net/?p=34
	http://www.lewei50.comwww.lewei50.com/dev/doc/90
	http://www.geek-workshop.com/thread-1824-1-1.html
	http://www.arduino.cn/thread-3157-1-1.html
	
	


#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.boboking.com";
IPAddress ip(192,168,1,177);
EthernetClient client;
 
// remote website name
char website[] PROGMEM = "www.lewei50.com";
char urlBuf[] PROGMEM = "/api/V1/gateway/UpdateSensors/01"; // 01应该更改为你对应的网关标识
char apiKey[] PROGMEM = "userkey:4a7c908d0de946de96e041dd84834154"; //需要更改为你的userkey
byte Ethernet::buffer[700];
static long timer;
 
// called when the client request is complete
static void my_result_cb (byte status, word off, word len) {
  Serial.print("<<< reply ");
  Serial.print(millis() - timer);
  Serial.println(" ms");
  Serial.println((const char*) Ethernet::buffer + off);
}
 
void setup () {

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
