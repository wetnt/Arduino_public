#include "B3_ePaper.h"
String filename = "santi45.txt";
void setup() {
  //----------------------------------------------------------
  lgsetup("ePaper SD"); delay(200);
  Serial2.begin(115200); delay(200);
  while (!Serial2) {
    ;
  }
  //----------------------------------------------------------
  SD_setup();
  sd_file_init();
  sd_book_read_show(filename, 0);
  delay(2000);
  //----------------------------------------------------------
}
void loop() {
  Serial_Loop(); delay(2);
}
char sBuff[100];
int sN = 0;
void Serial_Loop(void) {
  while (Serial2.available() > 0) {
    byte b = Serial2.read();
    Serial.write(b);
  }
  while (Serial.available() > 0) {
    //Serial2.write(Serial.read());
    char b = Serial.read(); lg(b);
    sBuff[sN++] = b;
    if ( b == '\n' || b == '\r' ) {
      int pagex = String(sBuff).toInt();
      lg("sBuff==="); lg(pagex); lg();
      sd_book_read_show(filename, pagex);
      resetBuffer(sBuff); sN = 0;
    }
  }
}
static void smartDelay(unsigned long ms) {
  //------------------------------------------
  unsigned long start = millis();
  do {
    //-------------------------------
    Serial_Loop(); delay(2);
    //-------------------------------
  } while (millis() - start < ms);
  //------------------------------------------
}

