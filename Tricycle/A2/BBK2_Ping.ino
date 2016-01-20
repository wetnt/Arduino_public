#include <NewPing.h>
//------------------------------------------------------
#define TRIGGER_PIN  13
#define ECHO_PIN     12
#define MAX_DISTANCE 999 //999cm=9.99m
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).
//------------------------------------------------------
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
unsigned long pingTimer;
unsigned int ping_cm = 999;
//------------------------------------------------------
void PingSetup() {
  pingTimer = millis();
}
void PingLoop() {
  //------------------------------------------------------
  if (millis() <= pingTimer) return;
  pingTimer += PING_INTERVAL;
  //------------------------------------------------------
  if (sonar.check_timer())
    ping_cm = sonar.ping_result / US_ROUNDTRIP_CM;
  //------------------------------------------------------
  Tricycle_ping_cm = ping_cm;
  //------------------------------------------------------
  //ping_cm = sonar.ping() / US_ROUNDTRIP_CM;
  //if (ping_cm == 0) ping_cm = MAX_DISTANCE;
  //------------------------------------------------------
}
//------------------------------------------------------
float PingGetCM() {
  return ping_cm;
}
void PingShow() {
  lg("Ping: "); lg(ping_cm); lg("cm"); lg();
}
//------------------------------------------------------
