#include <avr/pgmspace.h>
//---------------------------------------------------------------------------------------------
//const static char Lewei_Link[] PROGMEM = {"AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80"};
String S(const char x[]) {
  char myChar; String myBuffer = "";
  int len = strlen_P(x);
  for (int k = 0; k < len; k++) {
    myChar =  pgm_read_byte_near(x + k);
    myBuffer += myChar;
  }
  return myBuffer;
}
//char* C(const char x[]) {
//  int len = strlen_P(x);
//  char myBuffer[len + 1]; char myChar;
//  for (int k = 0; k < len; k++) {
//    myChar = pgm_read_byte_near(x + k);
//    myBuffer[k] = myChar;
//  }
//  myBuffer[len] = '\0';
//  return myBuffer;
//}
int L(const char x[]) {
  return strlen_P(x);
}
//---------------------------------------------------------------------------------------------
