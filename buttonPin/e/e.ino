
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
  if(digitalRead(ButtonPin)==HIGH) //检测电平变高
  {
    //------------------------------------------------------
    WorkRun(ButtonPin);
    //------------------------------------------------------
    delay(20);  
    //延时一段时间，防止按钮突然断开再按下。
    //判断按钮状态，如果仍然按下的话，等待松开。
    //------------------------------------------------------
    while(digitalRead(ButtonPin)==HIGH) 
    {
      delay(10);
    }
    //------------------------------------------------------
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
    WorkRunA(); 
    break;
  case ButtonPinB: 
    WorkRunB(); 
    break;
  case ButtonPinC: 
    WorkRunC(); 
    break;
  case ButtonPinD: 
    WorkRunD(); 
    break;
  case ButtonPinE: 
    WorkRunE(); 
    break;
  case ButtonPinF: 
    WorkRunF(); 
    break;
  }
  //------------------------------------------
}

void WorkRunA(){
  Keyboard.print("wetnt");
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll();
}
void WorkRunB(){
  Keyboard.println("wetnt123");
}
void WorkRunC(){
  Keyboard.print("wetnt@sina.com");
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll();
}
void WorkRunD(){
  Keyboard.println("wetntxjp");
}
void WorkRunE(){
  ButtonKey_Ctrl_C();
}
void WorkRunF(){
  ButtonKey_Ctrl_V();
}
//==========================================
void ButtonKey_Ctrl_C(){//Ctrl+c
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(67);//c
  delay(100);
  Keyboard.releaseAll();
}
void ButtonKey_Ctrl_V(){//Ctrl+v
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(86);//v
  delay(100);
  Keyboard.releaseAll();
}

void WorkRunEx(){
  Keyboard.print("boboking");
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll();
}
void WorkRunFx(){
  //------------------------------------------
  Keyboard.println("boboking");
  return;
  //------------------------------------------
  // CTRL-ALT-DEL:
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  delay(100);
  Keyboard.releaseAll();
  //ALT-s:
  delay(2000);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('l');
  Keyboard.releaseAll();
  //------------------------------------------
  return;
  //Keyboard.press(KEY_LEFT_CTRL);
  //Keyboard.press(KEY_LEFT_ALT);
  //Keyboard.press(KEY_DELETE);
  Keyboard.println("wetnt123");
  //------------------------------------------
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT); 
  Keyboard.press('Q');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.write(KEY_RETURN);  
  //------------------------------------------
}

/*
开关连接实验
 接线方法:
 材料：一个轻触开关、一个10kΩ电阻，一个0.1uF电容（可选）
 连接方法：
 开关接在Arduino D3和+5V之间；
 10kΩ电阻接在Arduino D3和GND之间；
 0.1uF电容接在Arduino D3和+5V之间（可以不用电容）；
 
 74
 65
 32 
 */



