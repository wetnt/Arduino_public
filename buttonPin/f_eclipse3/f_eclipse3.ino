
int n = 0;
int InData0 = 0;

void setup()
{
  Serial.begin(115200);
}

void loop()
{  
  InData0 = analogRead(A0); 
  n = GetKeyNumber(InData0);
  Serial.println(n);
  if(n>0){
	WorkRun(n);
  }
  delay(100);
}

//================================================
int k = 85;
int m = 85/8;
int GetKeyNumber(int a){
  for(int i = 1;i<13;i++){
    if(k*i-m<a && a<k*i+m ){ 
      return 13-i;
    }
  }
  return 0;
}
//================================================



//================================================
const int BB1 = 1, BB2 = 2, BB3 = 3;
const int BB4 = 4, BB5 = 5, BB6 = 6;
const int BB7 = 7, BB8 = 8, BB9 = 9;
const int BBX = 10,BBY = 11,BBZ = 12;
//================================================
void WorkRun(int ButtonPin){
  //------------------------------------------
  Serial.print("ButtonPin=");
  Serial.println(ButtonPin);
  //------------------------------------------
  switch (ButtonPin) {
  //------------------------------------------
  case BB1: WorkRun_Ctrl_C(); break;
  case BB2: WorkRun_Ctrl_V(); break;
  case BB3: WorkRun_Delete(); break;
  //------------------------------------------
  case BB4: WorkRun_Ctrl_Shift_F(); break;
  case BB5: WorkRun_Alt_Shift_R(); break;
  case BB6: WorkRun_Ctrl_Xg(); break;
  //------------------------------------------
  case BB7: WorkRun_F3(); break;
  case BB8: WorkRun_Ctrl_Alt_H(); break;
  case BB9: WorkRun_Alt_Xg(); break;  
  //------------------------------------------
  case BBX: WorkRun_BOBOKing(); break;
  case BBY: WorkRun_Wetnt(); break;
  case BBZ: WorkRun_Wetnt2(); break;  
  //------------------------------------------
  }
}

//================================================
//================================================
//================================================
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
void WorkRun_Delete(){
  Keyboard.press(KEY_DELETE);
  WorkRun_press_delay();
}
void WorkRun_Enter(){
  Keyboard.press(KEY_RETURN);
  WorkRun_press_delay();
}
//================================================
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
//================================================
void WorkRun_F3(){
  Keyboard.press(KEY_F3);
  WorkRun_press_delay();
}
void WorkRun_Ctrl_Alt_H(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(72);//H
  WorkRun_press_delay();
}
void WorkRun_Ctrl_1(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(49);//_1
  WorkRun_press_delay();
}
void WorkRun_Ctrl_X_number(){
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(111);//_/(小键盘)
  WorkRun_press_delay();
  //Ctrl+/(小键盘) 折叠当前类中的所有代码
  //Ctrl+×(小键盘) 展开当前类中的所有代码
}
//================================================
void WorkRun_press_delay(){
  delay(100);
  Keyboard.releaseAll();
}
//================================================
//================================================
//================================================
void WorkRun_BOBOKing(){
  Keyboard.print("boboking");
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll();
}
void WorkRun_Wetnt(){
  Keyboard.print("wetnt");
  Keyboard.press(KEY_TAB);
  delay(100);
  Keyboard.releaseAll();
}
void WorkRun_Wetnt2(){
  Keyboard.println("wetntxjp318");
}
//================================================
//================================================
