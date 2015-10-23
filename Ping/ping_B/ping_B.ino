//float cm = 0;
void setup() 
{ 
  Serial.begin(9600); 
  PingSetup(13,12);  
} 
void loop() 
{ 
  PingLoop();
  PingShow();
  delay(1000); 
} 

