int morse_beeps_pin = 7;
int morse_blink_pin = 13;
void setup() {
  //--------------------------------------------
  lgsetup("Morse Code Exp!");
  //--------------------------------------------
  pinMode(morse_beeps_pin, OUTPUT);
  pinMode(morse_blink_pin, OUTPUT);
  digitalWrite(morse_blink_pin, LOW);
  digitalWrite(morse_beeps_pin, HIGH);
  //--------------------------------------------
  //--------------------------------------------
}
void loop() {
  smartDelay(1000);
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
