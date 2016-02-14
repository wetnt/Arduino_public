//=====================================================
//数码管：共阳极、4位、带小数点
//=====================================================
int a = 6;
int b = 7;
int c = 8;
int d = 9;
int e = 10;
int f = 11;
int g = 12;
int p = 13;
//----------------------------
int d4 = 5;
int d3 = 4;
int d2 = 3;
int d1 = 2;
//=====================================================
//设置变量
int tubeBuf[6] = { -1, -1, -1, -1, -1, -1};//数码管显示，首位空闲,1234位，小数点位
int delayMs = 55;  //此处数值对时钟进行微调
//=====================================================
byte segs[7] = { a, b, c, d, e, f, g };
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
void Tube4_Init() {
  //--------------------------------------------
  pinMode(d1, OUTPUT); pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT); pinMode(d4, OUTPUT);
  //--------------------------------------------
  pinMode(a, OUTPUT); pinMode(b, OUTPUT);
  pinMode(c, OUTPUT); pinMode(d, OUTPUT);
  pinMode(e, OUTPUT); pinMode(f, OUTPUT);
  pinMode(g, OUTPUT); pinMode(p, OUTPUT);
  //--------------------------------------------
}
void Tube4_loop() {
  for (int i = 1; i < 5; i++) showOne(delayMs, i, tubeBuf[5] == i, tubeBuf[i]);
}
void Tube_set(int a, int b, int c, int d, int Dec) {//数码管显示，1234位，小数点位
  tubeBuf[1] = a;  tubeBuf[2] = b;
  tubeBuf[3] = c;  tubeBuf[4] = d;
  tubeBuf[5] = Dec;
}
//=====================================================
int n = 0;
int x = 20;
void Tube4_loop_test() {
  n++;
  int a = (n / x / 1000) % 10;
  int b = (n / x / 100) % 10;
  int c = (n / x / 10) % 10;
  int d = (n / x / 1) % 10;
  Tube_set(a, b, c, d, 2);
}
//=====================================================
void showOne(int delayMs, int index, boolean DecShow, int Number) { //延时,位数，小数点，数字(延时决定亮度)
  clearLEDs(); pickDigit(index);
  if (DecShow)      dispDec();
  if (Number >= 0)  lightSegments(Number);
  delayMicroseconds(delayMs);
}
void dispDec() { //设定开启小数点
  digitalWrite(p, LOW);
}
void clearLEDs() { //清屏
  digitalWrite(a, HIGH); digitalWrite(b, HIGH);
  digitalWrite(c, HIGH); digitalWrite(d, HIGH);
  digitalWrite(e, HIGH); digitalWrite(f, HIGH);
  digitalWrite(g, HIGH); digitalWrite(p, HIGH);
}
void pickDigit(int x) { //定义pickDigit(x),其作用是开启dx端口
  //--------------------------------------------
  digitalWrite(d1, HIGH); digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH); digitalWrite(d4, HIGH);
  //--------------------------------------------
  switch (x) {
    case 1: digitalWrite(d1, LOW); break;
    case 2: digitalWrite(d2, LOW); break;
    case 3: digitalWrite(d3, LOW); break;
    case 4: digitalWrite(d4, LOW); break;
  }
  //--------------------------------------------
}
void lightSegments(int x) { //点亮对应数字的数码管
  for (int i = 0; i < 7; i++) digitalWrite(segs[i], seven_seg_digits[x][i]);
}
//=====================================================

