static const String codeName = "MHz170_Nano_8266!";
//------------------------------------------------

#include "Nokia_5110.h"

#define RST A0
#define CE A1
#define DC A2
#define DIN A3
#define CLK A4

Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);

long t0;  //计时器
//char s[20];
void setup() {
  //------------------------------------------------
  lgsetup(codeName);
  ss_init(F("G5"), 12, 11, 9600, true);//String name, int rx, int tx, long btl, boolean lgKey
  //------------------------------------------------
  lcd.setContrast(60);
  lcd.print("Please Wait ...");
  delay(1000);
  lcd.clear();
  lcd.print("Hi there ");
  lcd.println(":D");
  lcd.setCursor(0, 5);
  lcd.println("1 2 3 ...");
  //------------------------------------------------
}

void loop() {
  //  t0 = millis();
  //  lcd.setCursor(0, 17);
  //  sprintf(s, "%d",t0);
  //  lcd.print(s);
  //  delay(200);
  //  //lcd.clear();
  //  if (mySerial.available()) {
  //    Serial.write(mySerial.read());
  //  }
  ss_feed();
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}

