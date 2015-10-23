int  tonepin = 8; //设置控制蜂鸣器的数字6脚

void ToneStart() {
  digitalWrite(tonepin, HIGH); //发声音
}
void ToneStops() {
  digitalWrite(tonepin, LOW); //不发声音
}
