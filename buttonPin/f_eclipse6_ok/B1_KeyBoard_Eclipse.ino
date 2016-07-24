#define KEY_LEFT_ARROW    0xD8
#define KEY_RIGHT_ARROW   0xD7
//================================================
void WorkRun_Ctrl_Shift_F() { //format//格式化代码
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('o');
  WorkRun_press_delay();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('f');
  WorkRun_press_delay();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('s');
  WorkRun_press_delay();
}
void WorkRun_Alt_Shift_R() {//rename//重命名
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('r');
  WorkRun_press_delay();
}
void WorkRun_Ctrl_Xg() {//注释代码
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press('/');//_/
}
//================================================
void WorkRun_Ctrl_F() { //查找xxx
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('f');
  WorkRun_press_delay();
}
void WorkRun_F3() {//查找函数声明
  Keyboard.press(KEY_F3);
}
void WorkRun_Ctrl_Alt_H() {//查找函数调用位置
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('h');//H
}
//================================================
void WorkRun_Alt_LeftArrow() {//后退历史记录 Alt+←
  Keyboard.press(KEY_RIGHT_ALT);
  Keyboard.press(KEY_LEFT_ARROW);//←
}
void WorkRun_Alt_RightArrow() {//前进历史记录 Alt+→
  Keyboard.press(KEY_RIGHT_ALT);
  Keyboard.press(KEY_RIGHT_ARROW);//→
}
void WorkRun_Alt_Xg() {//快捷提示
  Keyboard.press(KEY_RIGHT_ALT);
  Keyboard.press('/');//_/
}
//================================================
//Arduino的Key库不支持小键盘，很遗憾下面的没法用！
//================================================
void WorkRun_Ctrl_X_xing() {//展开
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(106);//_*
}
void WorkRun_Ctrl_X_number() {//折叠代码
  //Keyboard.press(KEY_RIGHT_CTRL);
  //Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(60);//_/(小键盘)
  //Ctrl+/(小键盘) 折叠当前类中的所有代码
  //Ctrl+×(小键盘) 展开当前类中的所有代码
}
//================================================
