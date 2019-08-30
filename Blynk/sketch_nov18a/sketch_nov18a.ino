//--------------------------------------------------
//#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>

#include <BlynkSimpleEsp32.h>
char auth[] = "a978f747568f49f591b2f8865c957b1d";

#include "SSD1306.h"
SSD1306  display(0x3c, 4, 15);
//--------------------------------------------------
void setup() {
  lgsetup("wifi test"); 
  //--------------------------------------------------
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW); delay(50);
  digitalWrite(16, HIGH);delay(50);
  //--------------------------------------------------
  lg("init");lg();
  display.init();
  //display.flipScreenVertically();
  display.setContrast(255);
  //--------------------------------------------------
  for (int16_t i = 0; i < DISPLAY_WIDTH; i += 4) {
    display.drawLine(0, 0, i, DISPLAY_HEIGHT - 1);
    display.display();
    delay(10);
  }
  delay(1000);
  //--------------------------------------------------
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(10,10,"temperatureRead");
  //display.println("temperatureRead");
  display.display();  
  lg("temperatureRead");lg();
  //--------------------------------------------------    
  lg("MMMM");lg();
  //Blynk.begin(auth, "JTFY", "jtfy2468");
  Blynk.begin(auth, "MMMM", "1234567890123");
  Blynk.connect();
  //--------------------------------------------------  
}
void loop() {
  //--------------------------------------------------
  float f = random(0, 1000) / 100;
  float t = temperatureRead();
  //--------------------------------------------------
  display.clear();
  display.drawString(10,10,String(t));
  display.display();
  lg(t);lg();
  //--------------------------------------------------
  Blynk.virtualWrite(V6, t);
  //--------------------------------------------------
  smartDelay(5 * 1000);
  //--------------------------------------------------
}
//===============================================
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    //lgFeed(); wfs_loop(); Dog_Loop();
    //Blynk.run();
    //------------------------------------------
  } while (millis() - start < ms);
}
//===============================================
