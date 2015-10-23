const int TrigPin = 13; 
const int EchoPin = 12; 
float cm; 
void PingSetup() 
{ 
  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT); 
} 
void PingLoop() 
{ 
  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW); 

  cm = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm 
  cm = (int(cm * 100.0)) / 100.0; //保留两位小数
  PingShow();
} 
void PingShow() 
{ 
  Serial.print(cm); 
  Serial.print("cm"); 
  Serial.println(); 
  delay(1000); 
} 

