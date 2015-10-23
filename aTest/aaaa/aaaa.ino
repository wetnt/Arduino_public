void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial2.print("Simple TinyGPS library v. "); 
}

void loop()
{
  if(Serial1.available()){
    char c = Serial1.read();
    Serial.print(c); 
    Serial2.print(c); 
  }
  //Serial.println("Simple TinyGPS library v. "); 
  //Serial2.println("Simple TinyGPS library v. "); 
  //delay(300);
}
