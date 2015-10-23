//=========================================
int IRR = 4;//定义右侧避障传感器接口
int IRM = 5;//定义中间避障传感器接口
int IRL = 6;//定义左侧避障传感器接口
int IRK_L,IRK_M,IRK_R;
//=========================================
void IR_Setup(int r, int m, int l)
{
  IRR = r;
  IRM = m;
  IRL = l;
  pinMode(IRR,INPUT);
  pinMode(IRM,INPUT);
  pinMode(IRL,INPUT);
}
//=========================================
void IR_Loop()
{
  IRK_R = digitalRead(IRR);
  IRK_M = digitalRead(IRM);
  IRK_L = digitalRead(IRL);
}
int IR_Get()
{
  if( IRK_R == LOW || IRK_M == LOW  || IRK_L == LOW )
  {
    return 5;
  }
  else{
    return 100;
  }
}
void IR_Show(bool delaykey)
{
  Serial.print(IRK_R); 
  Serial.print(" "); 
  Serial.print(IRK_M); 
  Serial.print(" "); 
  Serial.print(IRK_L); 
  Serial.print(" ");  
  Serial.println();
  if(delaykey) delay(200);
}
//=========================================

