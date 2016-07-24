int MainPin = A0;
int BtnKey = 0;

void KeyBoard_setup(int pin) {
  MainPin = pin;
  Keyboard.begin();
}
void KeyBoard_loop() {
  BtnKey = GetKeyNumber(analogRead(MainPin));
  if (BtnKey > 0) WorkRun(BtnKey);
}
//================================================
const static int k = 85, m = 85 / 8;
int GetKeyNumber(int a) {
  for (int i = 1; i < 13; i++) {
    if (k * i - m < a && a < k * i + m ) {
      return 13 - i;
    }
  }
  return 0;
}
//================================================
const static int BB1 = 1, BB2 = 2, BB3 = 3;
const static int BB4 = 4, BB5 = 5, BB6 = 6;
const static int BB7 = 7, BB8 = 8, BB9 = 9;
const static int BBX = 10, BBY = 11, BBZ = 12;
//================================================
void WorkRun(int ButtonPin) {
  //------------------------------------------
  lg(F("ButtonPin=")); lg(ButtonPin); lg();
  //------------------------------------------
  switch (ButtonPin) {
    //------------------------------------------
    case BB1: WorkRun_Ctrl_Shift_F(); break;//格式化代码
    case BB2: WorkRun_Alt_Shift_R(); break;//重命名
    case BB3: WorkRun_Ctrl_Xg(); break;//注释代码
    //------------------------------------------
    case BB4: WorkRun_F3(); break;//函数声明
    case BB5: WorkRun_Ctrl_Alt_H(); break;//函数调用
    case BB6: WorkRun_Ctrl_F(); break;//查找xxx
    //------------------------------------------
    case BB7: WorkRun_Alt_LeftArrow(); break;//后退历史记录 Alt+←
    case BB8: WorkRun_Alt_LeftArrow(); break;//前进历史记录 Alt+→
    case BB9: WorkRun_Alt_Xg(); break;//提示
    //------------------------------------------
    case BBX: WorkRun_WetntA(); break;
    case BBY: WorkRun_WetntC(); break;
    case BBZ: WorkRun_WetntB(); break;
      //------------------------------------------
  }
  WorkRun_press_delay();
}
//================================================
void WorkRun_press_delay() {
  delay(100); Keyboard.releaseAll();
}
//================================================
