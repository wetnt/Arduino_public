#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 6, 5, 4, 3);

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(4800);
  
    lcd.begin(16, 2);
  lcd.print("hello, world!");
  Serial.println("starttime");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  Serial.println("hello");
  
  lcd.clear();
  String sa =String("V=");// + String(" ") + String("A=")+String(Amp);
  String sb =String("W=");// + String(" ") + String("K=")+String(Kwh);
  lcd.setCursor(0,0); lcd.print(sa);
  lcd.setCursor(0,1); lcd.print(sb);
}
