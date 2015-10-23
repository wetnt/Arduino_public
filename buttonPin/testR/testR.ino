int InData0 = 0;
void setup()
{
  Serial.begin(115200);
}

void loop()
{  
  InData0 = analogRead(A0); 
  Serial.print("---------------");
  Serial.println(InData0);
  delay(100);  
}
