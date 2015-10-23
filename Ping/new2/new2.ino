#include <NewPing.h>

//------------------------------------------------------
#define TRIGGER_PIN  13 
#define ECHO_PIN     12
#define MAX_DISTANCE 200
//------------------------------------------------------
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//------------------------------------------------------
unsigned int pingSpeed = 50;
unsigned long pingTimer;
//------------------------------------------------------
unsigned int uS = 0;
//------------------------------------------------------

void PingSetup() {
  pingTimer = millis();
}
void PingLoop() {
  if (millis() >= pingTimer) {
    pingTimer += pingSpeed;
    sonar.ping_timer(echoCheck);
	PingShow();
  }
}
void echoCheck(){
  if (sonar.check_timer()) {
    uS = sonar.ping_result / US_ROUNDTRIP_CM;
  }
}

void PingShow(){
    Serial.print("Ping: ");
    Serial.print(uS);
    Serial.println("cm");
}
