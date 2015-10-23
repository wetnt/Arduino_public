
const int ButtonPinA = 7;
const int ButtonPinB = 4;
const int ButtonPinC = 6;
const int ButtonPinD = 5;
const int ButtonPinE = 3;
const int ButtonPinF = 2;

void setup(){
  //--------------------------------------
  Serial.begin(115200);
  Button_Setup();
  Keyboard.begin();
  //--------------------------------------
  Serial.print("ButtonPin Start......");
  //--------------------------------------
}
void loop(){
  Button_Loop();
}
void Button_Setup(){
  //--------------------------------------
  //按钮端子作为输入
  pinMode(ButtonPinA,INPUT);
  pinMode(ButtonPinB,INPUT);
  pinMode(ButtonPinC,INPUT);
  pinMode(ButtonPinD,INPUT);
  pinMode(ButtonPinE,INPUT);
  pinMode(ButtonPinF,INPUT);
  //--------------------------------------
}
void Button_Loop(){
  Button_Read(ButtonPinA);
  Button_Read(ButtonPinB);
  Button_Read(ButtonPinC);
  Button_Read(ButtonPinD);
  Button_Read(ButtonPinE);
  Button_Read(ButtonPinF);
}
void Button_Read(int ButtonPin){
  //------------------------------------------------------
  if(digitalRead(ButtonPin)==HIGH)
  {
    WorkRun(ButtonPin);
    delay(20);
    while(digitalRead(ButtonPin)==HIGH) 
    {
      delay(10);
    }
  }
  //------------------------------------------------------
}

void WorkRun(int ButtonPin){
  //------------------------------------------
  Serial.print("ButtonPin=");
  Serial.println(ButtonPin);
  //------------------------------------------
  switch (ButtonPin) {
  case ButtonPinA: 
    //WorkRun_Ctrl_C(); 
    WorkRun_Ctrl_Xg(); 
    break;
  case ButtonPinB: 
    //WorkRun_Ctrl_V(); 
    WorkRun_Alt_Xg();
    break;
  case ButtonPinC: 
    WorkRun_Ctrl_Shift_F(); 
    break;
  case ButtonPinD: 
    WorkRun_Alt_Shift_R(); 
    break;
  case ButtonPinE: 
    WorkRun_Alt_Xg(); 
    break;
  case ButtonPinF: 
    WorkRun_Ctrl_Xg(); 
    break;
  }
  //------------------------------------------
}
void WorkRun_Ctrl_C(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(67);//C
  WorkRun_press_delay();
}
void WorkRun_Ctrl_V(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(86);//V
  WorkRun_press_delay();
}
void WorkRun_Ctrl_Shift_F(){//format
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(70);//F
  WorkRun_press_delay();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(83);//S
  WorkRun_press_delay();
}
void WorkRun_Alt_Shift_R(){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(82);//R
  WorkRun_press_delay();
}
void WorkRun_Alt_Xg(){
  Keyboard.press(KEY_RIGHT_ALT);
  Keyboard.press(47);//_/
  WorkRun_press_delay();
}
void WorkRun_Ctrl_Xg(){
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press(47);//_/
  WorkRun_press_delay();
}
//==========================================
void WorkRun_press_delay(){
  delay(100);
  Keyboard.releaseAll();
}
//==========================================
