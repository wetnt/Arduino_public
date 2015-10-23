float cm = 0;
void setup() 
{ 
  Serial.begin(9600); 
  PingSetup(3,2);  
} 
void loop() 
{ 
  cm = PingLoop();
} 

