///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "avr/pgmspace.h"
#include "LedControl.h"
//http://www.wayoda.org/arduino/ledcontrol/
const int numDevices = 4;      // number of MAX7219s used
const long scrollDelay = 40;   // adjust scrolling speed
unsigned long bufferLong [14] = {0};
//LedControl(int dataPin, int clkPin, int csPin, int numDevices)
LedControl lc = LedControl(12, 11, 10, numDevices); //DataIn,CLK,LOAD(CS),设备数量为4

void Led_setup() {
  for (int x = 0; x < numDevices; x++) {
    lc.shutdown(x, false);      //The MAX72XX is in power-saving mode on startup
    lc.setIntensity(x, 2);      // Set the brightness to default value
    lc.clearDisplay(x);         // and clear the display
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void scrollFont() {
  for (int counter = 0x20; counter < 0x80; counter++) {
    loadBufferLong(counter);
    delay(scrollDelay);
  }
}
void scrollMessage(prog_uchar * messageString) {
  int counter = 0;
  int myChar = 0;
  do {
    // read back a char
    myChar =  pgm_read_byte_near(messageString + counter);
    if (myChar != 0) {
      loadBufferLong(myChar);
    }
    counter++;
  } while (myChar != 0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load character into scroll buffer
void loadBufferLong(int ascii) {
  if (ascii >= 0x20 && ascii <= 0x7f) {
    for (int a = 0; a < 7; a++) {
      unsigned long c = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + a);
      unsigned long x = bufferLong [a * 2];
      x = x | c; bufferLong [a * 2] = x;
    }
    byte count = pgm_read_byte_near(font5x7 + ((ascii - 0x20) * 8) + 7);
    for (byte x = 0; x < count; x++) {
      rotateBufferLong();
      printBufferLong();
      delay(scrollDelay);
    }
  }
}
// Rotate the buffer
void rotateBufferLong() {
  for (int a = 0; a < 7; a++) {
    unsigned long x = bufferLong [a * 2];
    byte b = bitRead(x, 31); x = x << 1;
    bufferLong [a * 2] = x;
    x = bufferLong [a * 2 + 1]; x = x << 1;
    bitWrite(x, 0, b);
    bufferLong [a * 2 + 1] = x;
  }
}
// Display Buffer on LED matrix
void printBufferLong() {
  for (int a = 0; a < 7; a++) {
    unsigned long x = bufferLong [a * 2 + 1];
    byte y = x; lc.setRow(3, a, y);
    x = bufferLong [a * 2];
    y = (x >> 24); lc.setRow(2, a, y);
    y = (x >> 16); lc.setRow(1, a, y);
    y = (x >> 8 ); lc.setRow(0, a, y);
  }
}
