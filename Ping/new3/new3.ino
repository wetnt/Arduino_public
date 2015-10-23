#include <NewPing.h>
//------------------------------------------------------
#define TRIGGER_PIN  13 
#define ECHO_PIN     12
#define MAX_DISTANCE 200
//------------------------------------------------------
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//------------------------------------------------------
unsigned int pingSpeed = 100;
unsigned long pingTimer;
//------------------------------------------------------
unsigned int ping_cm = 0;
//------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pingTimer = millis();
}
void loop() { 
  //------------------------------------------------------
  if (millis() >= pingTimer) {
    //------------------------------------------------------
    pingTimer += pingSpeed;
    //------------------------------------------------------
    //ping_cm = MAX_DISTANCE;
    sonar.ping_timer(echoCheck);
    //------------------------------------------------------
    PingShow();
    //------------------------------------------------------
  }
}
void echoCheck(){//bukexiugai
  if (sonar.check_timer()) {
    ping_cm = sonar.ping_result / US_ROUNDTRIP_CM;    
  }
  else{
    //ping_cm = MAX_DISTANCE;
  }
}
//------------------------------------------------------

void PingShow(){
  Serial.print("Ping: ");
  Serial.print(ping_cm);
  Serial.println("cm");
}



