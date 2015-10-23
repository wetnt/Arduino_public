int  tonepin = 8; //设置控制蜂鸣器的数字6脚
void setup()
{
  pinMode(tonepin, OUTPUT); //设置数字IO脚模式，OUTPUT为输出
}
void loop()
{
  digitalWrite(tonepin, HIGH); //发声音
  delay(2000);//延时1ms
  digitalWrite(tonepin, LOW); //不发声音
  delay(2000);//延时ms
}

