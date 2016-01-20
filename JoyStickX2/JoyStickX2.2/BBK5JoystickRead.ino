//====================================
int PinAX = A0, PinAY = A1, PinAK = A2;
int PinBX = A3, PinBY = A4, PinBK = A5;
//====================================
int IntAX = 0, IntAY = 0, IntAK = 0;
int IntBX = 0, IntBY = 0, IntBK = 0;
//====================================
int MidAX = 127, MidAY = 127;
int MidBX = 127, MidBY = 127;
//====================================
char JoyCmd[20];
char JoyExp[100];
int charReadN = -1;
//====================================
void JoystickSetup()
{
  //--------------------------------------------
  pinMode(PinAX, INPUT);
  pinMode(PinAY, INPUT);
  pinMode(PinAK, INPUT);
  pinMode(PinBX, INPUT);
  pinMode(PinBY, INPUT);
  pinMode(PinBK, INPUT);
  //--------------------------------------------
  JoystickFirstRun();
  //--------------------------------------------
}
void JoystickFirstRun() {
  //--------------------------------------------
  IntAX = readAxis(PinAX);
  IntAY = readAxis(PinAY);
  IntAK = readDigital(PinAK);
  //--------------------------------------------
  IntBX = readAxis(PinBX);
  IntBY = readAxis(PinBY);
  IntBK = readDigital(PinBK);
  //--------------------------------------------
  MidAX = IntAX;
  MidAY = IntAY;
  MidBX = IntBX;
  MidBY = IntBY;
  //--------------------------------------------
}
void JoystickReadRun() {
  //--------------------------------------------
  IntAX = readAxis(PinAX);
  IntAY = readAxis(PinAY);
  IntAK = readDigital(PinAK);
  //--------------------------------------------
  IntBX = readAxis(PinBX);
  IntBY = readAxis(PinBY);
  IntBK = readDigital(PinBK);
  //--------------------------------------------
  IntAX = GetCenterMapValue(IntAX, MidAX);
  IntAY = GetCenterMapValue(IntAY, MidAY);
  IntBX = GetCenterMapValue(IntBX, MidBX);
  IntBY = GetCenterMapValue(IntBY, MidBY);
  //--------------------------------------------
  IntAK = map(IntAK, 0, 1, 0, range);
  IntBK = map(IntBK, 0, 1, 0, range);
  //--------------------------------------------
}
void JoystickReadShow() {
  //--------------------------------------------
  lg(IntAX);  lg(" ");
  lg(IntAY);  lg(" ");
  lg(IntAK);  lg(" ");
  lg(IntBX);  lg(" ");
  lg(IntBY);  lg(" ");
  lg(IntBK);  lg(" ");
  lgln();
  //--------------------------------------------
}
void JoystickShowLcd() {
  //--------------------------------------------
  //1横滚2俯仰3油门4偏航
  sprintf(JoyCmd, "$%02X%02X%02X%02X%02X%02X*\0", IntBX, IntBY, IntAY, IntAX, IntBK, IntAK);
  LcdShow(0, 0, JoyCmd);
  APC220_Send(JoyCmd, true);
  lg(JoyCmd); lgln();
  //--------------------------------------------
}
void JoyExpChar(char c) {
  if (c == '$') {
    charReadN = -1; JoyExpClear();
  }
  JoyExp[charReadN++] = c;
  if (c == '*') {
    lg(JoyExp); LcdClear(); LcdShow(0, 1, JoyExp);
  }
}
void JoyExpClear() {
  for (int i = 0; i < 100; i++) JoyExp[i] = '\0';
}

