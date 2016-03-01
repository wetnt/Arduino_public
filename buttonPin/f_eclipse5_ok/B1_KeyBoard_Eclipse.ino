//================================================
void WorkRun_Ctrl_Shift_F() { //eclipse_format
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('f');
  WorkRun_press_delay();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('s');
  WorkRun_press_delay();
}
void WorkRun_Alt_Shift_R() {//eclipse_rename
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('r');
  WorkRun_press_delay();
}
void WorkRun_Alt_Xg() {//eclipse_
  Keyboard.press(KEY_RIGHT_ALT);
  Keyboard.press('/');//_/
}
void WorkRun_Ctrl_Xg() {//eclipse_
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press('/');//_/
}
//================================================
void WorkRun_F3() {
  Keyboard.press(KEY_F3);
}
void WorkRun_Ctrl_Alt_H() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('h');//H
}
void WorkRun_Ctrl_1() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(49);//_1
}
void WorkRun_Ctrl_X_number() {
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press(KEY_RIGHT_SHIFT);
  Keyboard.press(111);//_/(小键盘)
  //Ctrl+/(小键盘) 折叠当前类中的所有代码
  //Ctrl+×(小键盘) 展开当前类中的所有代码
}
//================================================
