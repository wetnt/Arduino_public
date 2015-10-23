#include <SPI.h>
#include <Ethernet.h>
#include <LeweiClient.h>
//----------------------------------------------------
#define USERKEY          "4a7c908d0de946de96e041dd84834154" // BOBOKing_Lewei_ID
#define LW_GATEWAY       "01" // BOBOKing_Lewei_GAT
long LeWeiTime = millis(), LeWeiTimeKey = 10*1000;
//----------------------------------------------------  
LeWeiClient *lwc;
//----------------------------------------------------
byte my_mac[] = {
  0x74,0x69,0x69,0x2D,0x30,0x31};
//----------------------------------------------------
IPAddress mylwip(192,168,1,18);
IPAddress mylwgw(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress my_dns(202,106,196,115); 
//----------------------------------------------------
void LEWEI_Setup() {
  //----------------------------------------------------
  Serial.println("LeWeiClient......");
  lwc = new LeWeiClient(USERKEY, LW_GATEWAY);
  //----------------------------------------------------
  IPAddress ips = Ethernet.localIP();
  Serial.println(ips);
  //----------------------------------------------------
}
//----------------------------------------------------
void LEWEI_Loop() {
  //---------------------------------------
  if( millis() - LeWeiTime < LeWeiTimeKey) return; 
  LeWeiTime = millis();
  //---------------------------------------
  lwc->append("YDL", Kwhs);
  lwc->append("GL", Watt);
  lwc->append("DL", Amps); 
  lwc->append("DY", Volt); 
  lwc->append("GLYS", Pfss);
  //---------------------------------------
  lwc->append("WD", DHT_WD); 
  lwc->append("SD", DHT_SD); 
  //---------------------------------------     
  lwc->send();
  //---------------------------------------
}

