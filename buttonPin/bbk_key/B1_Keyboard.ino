//================================================
void kp(String s) {
  Keyboard.print(s);
}
//================================================
void kd() {
  delay(100);
}
void ktab() {
  Keyboard.press(KEY_TAB);
}
void kr() {
  Keyboard.releaseAll();
}
void kdr() {
  delay(100);
  Keyboard.releaseAll();
}
void kdtr() {
  delay(100);
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
}
//================================================
