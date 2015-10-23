//===================================================================
void Blink_setup() {
  pinMode(13, OUTPUT);
}
bool LightKey = false;
void Blink_work() {
  LightKey = !LightKey;
  if (LightKey) {
    digitalWrite(13, HIGH);  lgs.println("HIGH");  //delay(1000);
  } else {
    digitalWrite(13, LOW);   lgs.println("LOW");   //delay(1000);
  }
}
//===================================================================
