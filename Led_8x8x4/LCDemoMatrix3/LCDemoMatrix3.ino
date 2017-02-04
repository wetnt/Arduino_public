typedef const unsigned char prog_uchar;

void setup() {
  Led_setup();
  int myChar = pgm_read_byte_near(scrollText);
  loadBufferLong(myChar);
}

void loop() {
  //scrollMessage(scrollText);
  //scrollFont();
}
////////////////////////////////////////////////////

