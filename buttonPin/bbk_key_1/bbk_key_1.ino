const static int Pin2 = 2;
const static int Pin3 = 3;
const static int Pin4 = 4;
const static int Pin5 = 5;
const static int Pin6 = 6;
const static int Pin7 = 7;
const static int Buttons[] = {Pin2, Pin3, Pin4, Pin5, Pin6, Pin7};
const static int PinLn = 6;//sizeof(Buttons);
//47
//65
//32
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
  //47
  //65
  //32
  switch (ButtonPin) {
    case Pin7: kp("wetnt"); kdtr(); break;
    case Pin4: kp("wetnt123"); kdr(); break;
    case Pin6: kp("wetnt@sina.com"); kdtr(); break;
    case Pin5: kp("wetntxjp318"); kdr(); break;
    case Pin3: kp("shaochidian318"); kdr(); break;
    case Pin2: kp("142401197703110912"); kdr(); break;
  }
  //------------------------------------------
}
//==========================================
