//===================================================================
const static char sA[] PROGMEM = ".-";
const static char sB[] PROGMEM = "-...";
const static char sC[] PROGMEM = "-.-.";
const static char sD[] PROGMEM = "-..";
const static char sE[] PROGMEM = ".";
const static char sF[] PROGMEM = "..-.";
const static char sG[] PROGMEM = "--.";
const static char sH[] PROGMEM = "....";
const static char sI[] PROGMEM = "..";
const static char sJ[] PROGMEM = ".---";
const static char sK[] PROGMEM = "-.-";
const static char sL[] PROGMEM = ".-..";
const static char sM[] PROGMEM = "--";
const static char sN[] PROGMEM = "-.";
const static char sO[] PROGMEM = "---";
const static char sP[] PROGMEM = ".--.";
const static char sQ[] PROGMEM = "--.-";
const static char sR[] PROGMEM = ".-.";
const static char sS[] PROGMEM = "...";
const static char sT[] PROGMEM = "-";
const static char sU[] PROGMEM = "..-";
const static char sV[] PROGMEM = "...-";
const static char sW[] PROGMEM = ".--";
const static char sX[] PROGMEM = "-..-";
const static char sY[] PROGMEM = "-.--";
const static char sZ[] PROGMEM = "--..";
//===================================================================
const static char s0[] PROGMEM = "-----";
const static char s1[] PROGMEM = ".----";
const static char s2[] PROGMEM = "..---";
const static char s3[] PROGMEM = "...--";
const static char s4[] PROGMEM = "....-";
const static char s5[] PROGMEM = ".....";
const static char s6[] PROGMEM = "-....";
const static char s7[] PROGMEM = "--...";
const static char s8[] PROGMEM = "---..";
const static char s9[] PROGMEM = "----.";
//===================================================================
const static char* letters[] = {sA, sB, sC, sD, sE, sF, sG, sH, sI, sJ, sK, sL, sM, sN, sO, sP, sQ, sR, sS, sT, sU, sV, sW, sX, sY, sZ};
const static char* numbers[] = {s0, s1, s2, s3, s4, s5, s6, s7, s8, s9};
//===================================================================
//间隔时间：滴1t；嗒3t；滴嗒间1t；字符间3t；字间7t。
int dotDelay = 100;
//===================================================================
void Morse_String_Run(String s) {
  int n = s.length();//lg(n); lg();
  for (int i = 0; i < n; i++) {
    Morse_Exp(s[i]);
  }
}
void Morse_Exp(char ch) {
  //------------------------------------------------------
  String x = "";
  if (ch >= 'a' && ch <= 'z')       x = S(letters[ch - 'a']);
  else if (ch >= 'A' && ch <= 'Z')  x = S(letters[ch - 'A']);
  else if (ch >= '0' && ch <= '9')  x = S(numbers[ch - '0']);
  else if (ch == ' ') {}
  //------------------------------------------------------
  if (x.length() > 0) {
    lg(ch); lg('\t'); lg(x); lg('\t');
    flashSequence(x);
    lg();
  }
  //------------------------------------------------------
  smartDelay(dotDelay * 4);
  //------------------------------------------------------
}
void flashSequence(String sequence) {
  int n = sequence.length();
  for (int i = 0; i < n; i++) flashDotOrDash(sequence[i]);
  smartDelay(dotDelay * 3);//gap between letters//字符间3t
}
void flashDotOrDash(char dotOrDash) {
  lg(dotOrDash);
  Morse_Run(true);
  if (dotOrDash == ' ') {}
  else if (dotOrDash == '.') smartDelay(dotDelay);//滴1t
  else if (dotOrDash == '-') smartDelay(dotDelay * 3);//嗒3t
  Morse_Run(false);
  smartDelay(dotDelay);//gap between flashes//滴嗒间1t
}
//===================================================================
void Morse_Run(boolean openKey) {
  digitalWrite(13, openKey ? HIGH : LOW);
}
//===================================================================

