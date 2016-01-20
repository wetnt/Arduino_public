//=========================================
//定义避障传感器接口/右/中/左
int IRR = 4, IRM = 5, IRL = 6;
int IRK_L, IRK_M, IRK_R;
//=========================================
void IR_Setup(int r, int m, int l) {
  IRR = r; IRM = m; IRL = l;
  pinMode(IRR, INPUT);
  pinMode(IRM, INPUT);
  pinMode(IRL, INPUT);
}
//=========================================
void IR_Loop() {
  IRK_R = digitalRead(IRR);
  IRK_M = digitalRead(IRM);
  IRK_L = digitalRead(IRL);
}
int IR_Get() {
  if ( IRK_R == LOW || IRK_M == LOW  || IRK_L == LOW )
    return 5;
  else
    return 100;
}
void IR_Show(bool delaykey) {
  lg(IRK_R); lg(" "); lg(IRK_M); lg(" "); lg(IRK_L); lg(" "); lg();
  if (delaykey) delay(200);
}
//=========================================

