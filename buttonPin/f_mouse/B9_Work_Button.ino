//==========================================
void WorkRun_Ctrl_Shift_F() { //format
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(70);//F
  WorkRun_press_delay();
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(83);//S
  WorkRun_press_delay();
}
void WorkRun_Alt_Shift_R() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(82);//R
  WorkRun_press_delay();
}
void WorkRun_Alt_Xg() {
  Keyboard.press(KEY_RIGHT_ALT);
  Keyboard.press(47);//_/
  WorkRun_press_delay();
}
void WorkRun_Ctrl_Xg() {
  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press(47);//_/
  WorkRun_press_delay();
}
//==========================================
