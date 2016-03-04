const static int PinCC = A1;
const static int PinCV = A0;
const static int PinDL = A2;
const static int PinEN = A3;
const static int Buttons[] = {PinCC, PinCV, PinDL, PinEN};
const static int PinLn = 4;//sizeof(Buttons);
void setup() {
  //--------------------------------------
  lgsetup("ButtonPin Start......");
  Button_Setup();
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
//==========================================
