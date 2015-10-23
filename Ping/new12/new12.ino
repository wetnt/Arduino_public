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
//------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pingTimer = millis();
}

void loop() {
  // Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
    sonar.ping_timer(echoCheck); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
  // Do other stuff here, really. Think of it as multi-tasking.
}

void echoCheck() { // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
    Serial.print("Ping: ");
    Serial.print(sonar.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
    Serial.println("cm");
  }
  // Don't do anything here!
}
