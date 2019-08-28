#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

char auth[] = "a978f747568f49f591b2f8865c957b1d";

BLYNK_WRITE(V1) {
  TimeInputParam t(param);

  if (t.hasStartTime()){
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute() + ":" +
                   t.getStartSecond());
  }else if (t.isStartSunrise()){
    Serial.println("Start at sunrise");
  }else if (t.isStartSunset()){
    Serial.println("Start at sunset");
  }else{
  }

  if (t.hasStopTime()){
    Serial.println(String("Stop: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute() + ":" +
                   t.getStopSecond());
  }else if (t.isStopSunrise()){
    Serial.println("Stop at sunrise");
  }else if (t.isStopSunset()){
    Serial.println("Stop at sunset");
  }else{
    // Do nothing: no stop time was set
  }

  Serial.println(String("Time zone: ") + t.getTZ());
  Serial.println(String("Time zone offset: ") + t.getTZ_Offset());

  for (int i = 1; i <= 7; i++) {
    if (t.isWeekdaySelected(i)) {
      Serial.println(String("Day ") + i + " is selected");
    }
  }

  Serial.println();
}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth);
}

void loop(){
  Blynk.run();
}
