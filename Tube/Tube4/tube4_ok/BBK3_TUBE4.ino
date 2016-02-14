//=====================================================
//数码管：共阳极、4位、带小数点
//=====================================================
int tube_d[4] = {2, 3, 4, 5};//选位
int tube_p[8] = {6, 7, 8, 9, 10, 11, 12, 13};//数码段
//=====================================================
//设置变量
int tubeBuf[6] = { -1, -1, -1, -1, -1, -1};//数码管显示，首位空闲,1234位，小数点位
int tubeDelay = 55;  //此处数值对时钟进行微调
//=====================================================
//byte segs[7] = { 1, 2, 3, 4, 5, 6, 7 };
byte seven_seg_digits[10][7] = {
  { 0, 0, 0, 0, 0, 0, 1 }, // = 0
  { 1, 0, 0, 1, 1, 1, 1 }, // = 1
  { 0, 0, 1, 0, 0, 1, 0 }, // = 2
  { 0, 0, 0, 0, 1, 1, 0 }, // = 3
  { 1, 0, 0, 1, 1, 0, 0 }, // = 4
  { 0, 1, 0, 0, 1, 0, 0 }, // = 5
  { 0, 1, 0, 0, 0, 0, 0 }, // = 6
  { 0, 0, 0, 1, 1, 1, 1 }, // = 7
  { 0, 0, 0, 0, 0, 0, 0 }, // = 8
  { 0, 0, 0, 0, 1, 0, 0 }  // = 9
};
//=====================================================
void Tube4_Init(int dd[], int pp[]) {
  for (int i = 0; i < 4; i++)  d[i] = dd[i];
  for (int i = 0; i < 8; i++)  p[i] = pp[i];
  for (int i = 0; i < 4; i++)  pinMode(tube_d[i], OUTPUT);
  for (int i = 0; i < 8; i++)  pinMode(tube_p[i], OUTPUT);
  for (int i = 0; i < 7; i++)  segs[i] = tube_p[i];
}
void Tube4_loop() {
  for (int i = 1; i < 5; i++) showOne(i, tubeBuf[5] == i, tubeBuf[i]);
}
void Tube_set(int a, int b, int c, int d, int Dec) {//数码管显示，1234位，小数点位
  tubeBuf[1] = a;  tubeBuf[2] = b; tubeBuf[3] = c;  tubeBuf[4] = d; tubeBuf[5] = Dec;
}
//=====================================================
void showOne(int index, boolean DecShow, int Number) { //延时,位数，小数点，数字(延时决定亮度)
  clearLEDs(); pickDigit(index);
  if (DecShow)      dispDec();
  if (Number >= 0)  lightSegments(Number);
  delayMicroseconds(tubeDelay);
}
void dispDec() { //设定开启小数点
  digitalWrite(p[7], LOW);
}
void clearLEDs() { //清屏
  for (int i = 0; i < 8; i++) digitalWrite(p[i], HIGH);
}
void pickDigit(int x) { //定义pickDigit(x),其作用是开启dx端口
  for (int i = 0; i < 4; i++) digitalWrite(tube_d[i], HIGH);
  digitalWrite(tube_d[x - 1], LOW);
}
void lightSegments(int x) { //点亮对应数字的数码管
  for (int i = 0; i < 7; i++) digitalWrite(segs[i], seven_seg_digits[x][i]);
}
//=====================================================

