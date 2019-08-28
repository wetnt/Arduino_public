#include <ESP.h>

void setup() {

  Serial.begin(115200);
  delay(10);
  Serial.println();

  // uint8_t getCpuFreqMHz();

}

void loop() {
  Serial.println(ESP.getCpuFreqMHz());
  Serial.println(ESP.getFlashChipSpeed());
  Serial.println(ESP.getCycleCount());
  //Serial.println(ESP.getVcc());
  Serial.println(ESP.getChipId());
  Serial.println();
  Serial.println("--------------------------");

  delay(1000);

}
