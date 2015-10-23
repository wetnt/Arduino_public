void setup() 
{ 
  Serial.begin(9600); 
  PingSetup(); 
} 
void loop() 
{ 
  PingLoop(); 
  delay(1000); 
} 

