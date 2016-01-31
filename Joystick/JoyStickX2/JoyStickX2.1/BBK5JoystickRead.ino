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
  if (IntBK == 1)
    JoystickFirstRun();
  //--------------------------------------------
  IntAX = GetCenterMapValue(IntAX, MidAX);
  IntAY = GetCenterMapValue(IntAY, MidAY);
  IntBX = GetCenterMapValue(IntBX, MidBX);
  IntBY = GetCenterMapValue(IntBY, MidBY);
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
  lgln("");
  //--------------------------------------------
}
void JoystickShowLcd() {
  //--------------------------------------------
  LcdShow(0, 0, "M");
  char sz[32];
  //sprintf(sz, "%02d,%02d,%02d %02d,%02d,%02d", IntAX, IntAY, IntAK, IntBX, IntBY, IntBK);
  sprintf(sz, "%02X%02X%02X%02X%02X%02X", IntAX, IntAY, IntBX, IntBY, IntAK, IntBK);
  LcdShow(0, 1, sz);
  //sprintf(sz, "%02d,%02d,%02d ", IntBX, IntBY, IntBK);
  //LcdShow(0, 2, sz);
  //--------------------------------------------
}

