#include <NewPing.h>
//------------------------------------------------------
#define TRIGGER_PIN  13 
#define ECHO_PIN     12
#define MAX_DISTANCE 500
//------------------------------------------------------
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//------------------------------------------------------
unsigned int pingSpeed = 20;
unsigned long pingTimer;
//------------------------------------------------------
unsigned int ping_cm = 500;
//------------------------------------------------------
void PingSetup() {
  pingTimer = millis();
}
void PingLoop() { 
  //------------------------------------------------------
  if (millis() >= pingTimer) {
    //------------------------------------------------------
    pingTimer += pingSpeed;
    //------------------------------------------------------
    ping_cm = sonar.ping() / US_ROUNDTRIP_CM;
    if(ping_cm==0)ping_cm = 500;
    //------------------------------------------------------
    PingShow();
    //------------------------------------------------------
  }
}
//------------------------------------------------------
float PingGetCM(){
  return ping_cm;
}
void PingShow(){
  Serial.print("Ping: ");
  Serial.print(ping_cm);
  Serial.println("cm");
}
//------------------------------------------------------



