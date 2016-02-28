const static int PinCC = 2;
const static int PinCV = 3;
const static int PinDL = 4;
const static int PinEN = 5;
const static int Buttons[] = {PinCC, PinCV, PinDL, PinEN};
const static int PinLn = 4;//sizeof(Buttons);
void setup() {
  //--------------------------------------
  lgsetup("ButtonPin Start......");
  Button_Setup();
  Keyboard.begin();
  //--------------------------------------
}
void loop() {
  Button_Loop();
}
//===========================================================
void Button_Setup() { //按钮端子作为输入
  // int n = sizeof(Buttons);//.length();
  for (int i = 0; i < PinLn; i++) pinMode( Buttons[i], INPUT);
}
void Button_Loop() {
  for (int i = 0; i < PinLn; i++) Button_Read(Buttons[i]);
}
void Button_Read(int ButtonPin) {
  if (digitalRead(ButtonPin) == HIGH) {
    WorkRun(ButtonPin); delay(10);
    while (digitalRead(ButtonPin) == HIGH) delay(10);
  }
}
void WorkRun(int ButtonPin) {
  //------------------------------------------
  lg("ButtonPin="); lg(ButtonPin); lg();
  //------------------------------------------
  switch (ButtonPin) {
    case PinCC: WorkRun_Ctrl_C(); break;
    case PinCV: WorkRun_Ctrl_V(); break;
    case PinDL: WorkRun_Delete(); break;
    case PinEN: WorkRun_Enters(); break;
  }
  //------------------------------------------
  WorkRun_press_delay();
  //------------------------------------------
}
void WorkRun_press_delay() {
  delay(100); Keyboard.releaseAll();
}
void WorkRun_Ctrl_C() {
  lg("WorkRun_Ctrl_C"); lg();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(67);//C
}
void WorkRun_Ctrl_V() {
  lg("WorkRun_Ctrl_V"); lg();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(86);//V
}
void WorkRun_Delete() {
  lg("WorkRun_Delete"); lg();
  Keyboard.press(46);
}
void WorkRun_Enters() {
  lg("WorkRun_Enters"); lg();
  Keyboard.press(13);delay(100); 
}
//==========================================
