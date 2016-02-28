int morse_beeps_pin = 7;
int morse_blink_pi2 = 8;
int morse_blink_pin = 13;
void setup() {
  //--------------------------------------------
  lgsetup("Morse Code Exp!");
  //--------------------------------------------
  pinMode(morse_blink_pin, OUTPUT);
  pinMode(morse_blink_pi2, OUTPUT);
  pinMode(morse_beeps_pin, OUTPUT);
  digitalWrite(morse_blink_pin, LOW);
  digitalWrite(morse_blink_pi2, LOW);
  digitalWrite(morse_beeps_pin, HIGH);
  //--------------------------------------------
  ss_setup(true);
  //--------------------------------------------
}
void loop() {
  smartDelay(1000);
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed();ss_loop();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
