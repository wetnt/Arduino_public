// sketch 08-01
#include <avr/pgmspace.h>
int ledPin = 13;
int dotDelay = 200;

PROGMEM const char sA[]  = ".-";
PROGMEM const char sB[]  = "-...";
PROGMEM const char sC[]  = "-.-.";
PROGMEM const char sD[]  = "-..";
PROGMEM const char sE[]  = ".";
PROGMEM const char sF[]  = "..-.";
PROGMEM const char sG[]  = "--.";
PROGMEM const char sH[]  = "....";
PROGMEM const char sI[]  = "..";
PROGMEM const char sJ[]  = ".---";
PROGMEM const char sK[]  = "-.-";
PROGMEM const char sL[]  = ".-..";
PROGMEM const char sM[]  = "--";
PROGMEM const char sN[]  = "-.";
PROGMEM const char sO[]  = "---";
PROGMEM const char sP[]  = ".--.";
PROGMEM const char sQ[]  = "--.-";
PROGMEM const char sR[]  = ".-.";
PROGMEM const char sS[]  = "...";
PROGMEM const char sT[]  = "-";
PROGMEM const char sU[]  = "..-";
PROGMEM const char sV[]  = "...-";
PROGMEM const char sW[]  = ".--";
PROGMEM const char sX[]  = "-..-";
PROGMEM const char sY[]  = "-.--";
PROGMEM const char sZ[]  = "--..";

PROGMEM const char* letters[] = {sA, sB, sC, sD, sE, sF, sG, sH, sI, sJ, sK, sL, sM,
                                 sN, sO, sP, sQ, sR, sS, sT, sU, sV, sW, sX, sY, sZ
                                };

PROGMEM const char s0[]  = "-----";
PROGMEM const char s1[]  = ".----";
PROGMEM const char s2[]  = "..---";
PROGMEM const char s3[]  = "...--";
PROGMEM const char s4[]  = "....-";
PROGMEM const char s5[]  = ".....";
PROGMEM const char s6[]  = "-....";
PROGMEM const char s7[]  = "--...";
PROGMEM const char s8[]  = "---..";
PROGMEM const char s9[]  = "----.";

PROGMEM const char* numbers[] = {s0, s1, s2, s3, s4, s5, s6, s7, s8, s9};

char buffer[6];

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  char ch;
  if (Serial.available() > 0)
  {
    ch = Serial.read();
    if (ch >= 'a' && ch <= 'z')
    {
      strcpy_P(buffer, (char*)pgm_read_word(&(letters[ch - 'a'])));
      flashSequence(buffer);
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
      strcpy_P(buffer, (char*)pgm_read_word(&(letters[ch - 'A'])));
      flashSequence(buffer);
    }
    else if (ch >= '0' && ch <= '9')
    {
      strcpy_P(buffer, (char*)pgm_read_word(&(letters[ch - '0'])));
      flashSequence(buffer);
    }
    else if (ch == ' ')
    {
      delay(dotDelay * 4);  // gap between words
    }
  }
}

void flashSequence(char* sequence)
{
  int i = 0;
  while (sequence[i] != NULL)
  {
    flashDotOrDash(sequence[i]);
    i++;
  }
  delay(dotDelay * 3);    // gap between letters
}

void flashDotOrDash(char dotOrDash)
{
  digitalWrite(ledPin, HIGH);
  if (dotOrDash == '.')
  {
    delay(dotDelay);
  }
  else // must be a dash
  {
    delay(dotDelay * 3);
  }
  digitalWrite(ledPin, LOW);
  delay(dotDelay); // gap between flashes
}
