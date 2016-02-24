#include <avr/pgmspace.h>


// save some unsigned ints
const PROGMEM  uint16_t charSet[]  = { 65000, 32796, 16843, 10, 11234};

// save some chars
const char signMessage[] PROGMEM  = {"I AM PREDATOR,  UNSEEN COMBATANT. CREATED BY THE UNITED STATES DEPART"};
const static char Lewei_Link[] PROGMEM  = {"AT+CIPSTART=\"TCP\",\"www.lewei50.com\",80"};

unsigned int displayInt;
int k;    // counter variable
char myChar;

char buffer[30];
void setup() {
  Serial.begin(115200);
  while (!Serial);

  // put your setup code here, to run once:
  // read back a 2-byte int
  for (k = 0; k < 5; k++)
  {
    displayInt = pgm_read_word_near(charSet + k);
    Serial.println(displayInt);
  }
  Serial.println();

  // read back a char
  int len = strlen_P(signMessage);
  for (k = 0; k < len; k++)
  {
    myChar =  pgm_read_byte_near(signMessage + k);
    Serial.print(myChar);
  }

  Serial.println();
//-------------------------------------------------------------
//   strcpy_P(buffer, (char*)pgm_read_word(&*signMessage)); 
//    Serial.println(buffer);
String x = "";
 len = strlen_P(signMessage);
  for (k = 0; k < len; k++)  {
    myChar =  pgm_read_byte_near(signMessage + k);
    x+=myChar;
  }
  Serial.println(x);
  
}
void GetBuffer(const char x[]) {
  myBuffer = "";
  char myChar;
  int len = strlen_P(x);
  for (int k = 0; k < len; k++) {
    myChar =  pgm_read_byte_near(x + k);
    myBuffer += myChar;
  }
}
void loop() {
  // put your main code here, to run repeatedly:

}
