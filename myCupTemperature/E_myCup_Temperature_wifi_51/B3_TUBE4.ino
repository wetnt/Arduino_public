//=====================================================
//数码管：共阳极、4位、带小数点
//=====================================================
int tube_d[4] = {2, 3, 4, 5};//选位
int tube_p[8] = {6, 7, 8, 9, 10, 11, 12, 13};//数码段(7段+1小数点)
int tube_Buf[6] = { -1, -1, -1, -1, -1, -1};//数码管显示，首位空闲,1234位，小数点位
int tube_Delay = 55;  //数码管延时
int tube_Light = 10;  //数码管亮度调整，数值越大亮度越低，最亮0；
//=====================================================
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
void Tube4_Init(int dd[], int pp[], int light) {
  tube_Light = light;
  for (int i = 0; i < 4; i++)  tube_d[i] = dd[i];
  for (int i = 0; i < 8; i++)  tube_p[i] = pp[i];
  for (int i = 0; i < 4; i++)  pinMode(tube_d[i], OUTPUT);
  for (int i = 0; i < 8; i++)  pinMode(tube_p[i], OUTPUT);
}
void Tube4_loop() {
  for (int i = 1; i < 5; i++) showOne(i, tube_Buf[5] == i, tube_Buf[i]);
}
void Tube4_set(int a, int b, int c, int d, int Dec) {//数码管显示，1234位，小数点位
  tube_Buf[1] = a;  tube_Buf[2] = b; tube_Buf[3] = c;  tube_Buf[4] = d; tube_Buf[5] = Dec;
}
//=====================================================
void showOne(int index, boolean DecShow, int Number) { //延时,位数，小数点，数字(延时决定亮度)
  //-----------------------------------------------------------------------
  clearLEDs(); 
  //-----------------------------------------------------------------------
  pickDigit(index);
  if (DecShow)      dispDec();
  if (Number >= 0)  lightSegments(Number);
  delayMicroseconds(tube_Delay);
  //-----------------------------------------------------------------------
  clearLEDs(); delayMicroseconds(tube_Delay * tube_Light); //数码管亮度调整
  //-----------------------------------------------------------------------
}
void dispDec() { //设定开启小数点
  digitalWrite(tube_p[7], LOW);
}
void clearLEDs() { //清屏
  for (int i = 0; i < 8; i++) digitalWrite(tube_p[i], HIGH);
}
void pickDigit(int x) { //定义pickDigit(x),其作用是开启dx端口
  for (int i = 0; i < 4; i++) digitalWrite(tube_d[i], HIGH);
  digitalWrite(tube_d[x - 1], LOW);
}
void lightSegments(int x) { //点亮对应数字的数码管
  for (int i = 0; i < 7; i++) digitalWrite(tube_p[i], seven_seg_digits[x][i]);
}
//=====================================================

