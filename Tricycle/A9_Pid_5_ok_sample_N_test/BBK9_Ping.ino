int TrigPin = A3;
int EchoPin = A2;
float Ping_cm = 0;
//----------------------------------------------------
unsigned long PingTime = millis();
int PingTimeKey = 1000;
//----------------------------------------------------
void PingSetup(int trig, int echo)
{
  TrigPin = trig;
  EchoPin = echo;
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}
float PingLoop()
{
  //----------------------------------------------------
  if ( millis() - PingTime < PingTimeKey) return Ping_cm;
  PingTime = millis();
  //----------------------------------------------------
  //低高低电平发一个短时间脉冲去TrigPin
  digitalWrite(TrigPin, LOW );
  smartDelay(2);//delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  smartDelay(10);//delayMicroseconds(10);
  digitalWrite(TrigPin, LOW );
  //----------------------------------------------------
  Ping_cm = pulseIn(EchoPin, HIGH) / 56.57; //将回波时间换算成cm //58
  Ping_cm = (int(Ping_cm * 100.0)) / 100.0; //保留两位小数
  //----------------------------------------------------
  PingLog();
  return Ping_cm;
  //----------------------------------------------------
}
float PingLog()
{
  lg(Ping_cm); lg("cm"); lg();
}
