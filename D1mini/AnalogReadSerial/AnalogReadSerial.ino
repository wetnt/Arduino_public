void setup() {
  Serial.begin(115200);
  //pinMode(D2,INPUT_PULLUP); 
  //pinMode(D2,OUTPUT);
  //digitalWrite(D2, LOW);
}
void loop() {
  int sensorValue = analogRead(D2);
  Serial.println(sensorValue);
  
  delay(1000);
}
