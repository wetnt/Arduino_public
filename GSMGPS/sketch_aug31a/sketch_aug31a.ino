void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  
  delay(5000);
  pinMode(5, OUTPUT);
  digitalWrite(13, LOW);
  delay(2000);  
   digitalWrite(13, HIGH); 
}

void loop() {
  if (Serial2.available())
  {
    char c = Serial2.read();
    Serial.write(c);
  }
  if (Serial.available())
  {
    char c = Serial.read();
    Serial3.write(c);
  }
}
