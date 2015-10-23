int buzzer = 6; //设置控制蜂鸣器的数字IO脚
void setup()
{
  pinMode(buzzer, OUTPUT); //设置数字IO脚模式，OUTPUT为输出
  //tone(buzzer, 800, 3000);
}
void loop()
{
  noTone(8);
  tone(6, 440, 2);
  delay(200);
  noTone(6);
  delay(5000);

  tone(7, 494, 5);
  delay(500);
  noTone(7);
}

