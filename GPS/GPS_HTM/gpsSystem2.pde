// GPS SYSTEM

/* Keys
 /
 /      1
 /  4  3 0
 /      2
 /
 */

#include <NewSoftSerial.h>
#include <TinyGPS.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <math.h>

union bitFloat {
      float float_num;
      char byte[4];
};

byte upArrow[8] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000
};

byte downArrow[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000
};

byte degree[8] = {
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000
};



LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int adcKeyIn;
int NUM_KEYS = 5;
int key=-1;
int oldKey=-1;
int adcKeyVal[5] ={
  30, 150, 360, 535, 760 };

// Options

boolean useCurrentSpeed = 0;
boolean useDirections = 0;
boolean useAbsoluteHeadings = 0;
byte timeZone = 0;

TinyGPS gps;
NewSoftSerial nss(3, 2);

// Maximum speed and last known position
float maxSpeed = 0;
float lastFlat = 0;
float lastFlon = 0;

// Default location to navigate from
float targetFlat = 49.88622;
float targetFlon = -97.15256;

// Current waypoint selected
byte waypoint = 1;

// To track time elasped for average speed calculation
byte startHour = 0;
byte startMinute = 0;
byte startSecond = 0;

// Default menu choice
byte screen = 0;

boolean started = 1;
long distance = 0;

const int DEBOUNCE_DELAY = 50;
byte screenRefresh = 120;

void gpsdump(TinyGPS &gps);
bool feedgps();
void printFloat(double f, int digits = 2);

void setup() { 
  Serial.begin(57600);
  nss.begin(4800);
  pinMode(13, OUTPUT);  //we'll use the debug LED to output a heartbeat

  lcd.createChar(0, upArrow);
  lcd.createChar(1, downArrow);
  lcd.createChar(2, degree);
  lcd.begin(16, 2);

  showSplash();

  // Load settings

  useCurrentSpeed = (boolean)EEPROM.read(0);
  useDirections = (boolean)EEPROM.read(1);
  useAbsoluteHeadings = (boolean)EEPROM.read(2);
  timeZone = EEPROM.read(3);

  showMenu();

}

void loop() {

  bool newdata = false;
  unsigned long start = millis();

  // Every 5 seconds we print an update
  while (millis() - start < 100)
  {
    if (feedgps())
      newdata = true;        
  }

  if (checkKeyDebounce() == 4)
    showNavigationMenu();

  if (newdata)
  {
    Serial.println("Acquired Data");
    Serial.println("-------------");
    gpsdump(gps);
    Serial.println("-------------");
    Serial.println();
  }
  else {
    Serial.println("No data");
  } 

}

int checkKeyDebounce() {

  adcKeyIn = analogRead(0); // read the value from the

  key = getKey(adcKeyIn); // convert into key press 

  if (key != oldKey) { // if keypress is detected 

    delay(50); // wait for debounce time

    adcKeyIn = analogRead(0); //read the value from the sensor

    key = getKey(adcKeyIn); // convert into key press

    if (key != oldKey) {

      oldKey = key;

      if (key >=0) {

        return key;

      }

      else 

        return -1;

    }

    else

        return -1; 

  }

  else

      return -1;

}

int getKeyDebounce() {
  // wait for no keypress, then return keypress held for debounce period
  adcKeyIn = analogRead(0);    // read the value from the sensor  
  key = getKey(adcKeyIn);		        // convert into key press
  do {
    key = getKey(analogRead(0));
  } 
  while (key != -1);
  oldKey = key;
  while (oldKey == -1 || key == -1 || key != oldKey) {
    oldKey = key;
    delay(DEBOUNCE_DELAY);
    key = getKey(analogRead(0));
  }
  return key;
}

// Convert ADC value to key number
int getKey(unsigned int input)
{
  int k;
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adcKeyVal[k])
    {
      return k;
    }
  }
  if (k >= NUM_KEYS)
    k = -1;     // No valid key pressed
  return k;
}


void printLCDFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
    lcd.print("-");
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  char sTemp[10];
  ltoa(int_part, sTemp, 10);
  lcd.print(sTemp);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    lcd.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    ltoa(toPrint, sTemp, 10);
    lcd.print(sTemp);
    remainder -= toPrint; 
  } 
}

void printFloat(double number, int digits)
{
  // Handle negative numbers
  if (number < 0.0)
  {
    Serial.print('-');
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  Serial.print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    Serial.print("."); 

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    Serial.print(toPrint);
    remainder -= toPrint; 
  } 
}

void gpsdump(TinyGPS &gps)
{

  if (screenRefresh == 120)
  { 
    lcd.clear();
    screenRefresh = 0;
  }
  else
    screenRefresh++;

  float flat, flon;
  unsigned long age;
  int year;
  byte month, day, hour, minute, second, hundredths;

  feedgps(); // If we don't feed the gps during this long routine, we may drop characters and get checksum errors

    gps.f_get_position(&flat, &flon, &age);

  Serial.print("Lat/Long(float): "); 
  printFloat(flat, 5); 
  Serial.print(", "); 
  printFloat(flon, 5);
  Serial.print(" Fix age: "); 
  Serial.print(age); 
  Serial.println("ms.");

  feedgps();

  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  Serial.print("Date: "); 
  Serial.print(static_cast<int>(month)); 
  Serial.print("/"); 
  Serial.print(static_cast<int>(day)); 
  Serial.print("/"); 
  Serial.print(year);
  Serial.print("  Time: "); 
  Serial.print(static_cast<int>(hour)); 
  Serial.print(":"); 
  Serial.print(static_cast<int>(minute)); 
  Serial.print(":"); 
  Serial.print(static_cast<int>(second)); 
  Serial.print("."); 
  Serial.print(static_cast<int>(hundredths));
  Serial.print("  Fix age: ");  
  Serial.print(age); 
  Serial.println("ms.");

  feedgps();

  Serial.print("Alt(cm): "); 
  Serial.print(gps.altitude()); 
  Serial.print(" Course(10^-2 deg): "); 
  Serial.print(gps.course()); 
  Serial.print(" Speed(10^-2 knots): "); 
  Serial.println(gps.speed());
  Serial.print("Alt(float): "); 
  printFloat(gps.f_altitude()); 
  Serial.print(" Course(float): "); 
  printFloat(gps.f_course()); 
  Serial.println();
  Serial.print("Speed(knots): "); 
  printFloat(gps.f_speed_knots()); 
  Serial.print(" (mph): ");  
  printFloat(gps.f_speed_mph());
  Serial.print(" (mps): "); 
  printFloat(gps.f_speed_mps()); 
  Serial.print(" (kmph): "); 
  printFloat(gps.f_speed_kmph()); 
  Serial.println();

  if (started == 1)
  {
    startHour = hour;
    startMinute = minute;
    startSecond = second;
  }

  float hours = (hour - startHour) + (((minute) - static_cast<float>(startMinute)) / 60) + (((second) - static_cast<float>(startSecond)) / 60 / 60);

  if ((gps.f_speed_kmph() > maxSpeed) && (gps.f_speed_kmph() < 1000))  // check for fastest speed and limit to 999 kmph
    maxSpeed = gps.f_speed_kmph();

  if (gps.f_speed_kmph() > 3.9)
  {
    if (started == 1)
    {
      started = 0;
      lastFlat = flat;
      lastFlon = flon;
    }
    else
    {
      distance = distance + calc_dist(flat, flon, lastFlat, lastFlon);
      lastFlat = flat;
      lastFlon = flon;
    }
  }

   if (age > 30000)
   {
   lcd.clear();
   lcd.setCursor(4, 0);
   lcd.print("WARNING!");
   lcd.setCursor(0, 1);
   lcd.print("Fix Age: ");
   printLCDFloat(age/1000, 0);
   lcd.print(" s");
   delay(3000);
   lcd.clear();
   }

  if (screen == 0)  // Latitude longitude speed and heading

  {

    lcd.setCursor(0, 0);
    printLCDFloat(flat, 5);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    printLCDFloat(flon, 5);
    lcd.print(" ");

    lcd.setCursor(12, 1);
    if (useDirections == 0) {
      if (gps.f_course()<100)
        lcd.print(" ");
          if (gps.f_course()<10)
        lcd.print(" ");
      printLCDFloat(gps.f_course(), 0);
      lcd.write(2);
    }
    else {
      lcd.print(" ");
      printHeadingDirection(gps.f_course());
    }
    lcd.setCursor(10, 0);
    if (gps.f_speed_kmph()<99.5)
      lcd.print(" ");
    if (gps.f_speed_kmph()<9.5)
      lcd.print(" ");
    printLCDFloat(gps.f_speed_kmph(), 0);
    lcd.print("kmh");

  }

  if (screen == 1)  // Distance, Average speed and maximum speed

  {

    lcd.setCursor(0, 0);
    lcd.print("Dist ");

    float fDist = distance;
    fDist /= 1000;

    float avgSpeed = 0;

    if (hours != 0)
      avgSpeed = fDist / hours;

    printLCDFloat(fDist, 3);

    lcd.print("km");

    lcd.setCursor(0, 1);
    lcd.print("Av/Mx ");

    printLCDFloat(avgSpeed, 0);
    lcd.print("/");
    printLCDFloat(maxSpeed, 0);
    lcd.print("kmh");

  }

  if ((screen == 2)||(screen == 3))  // Navigate to Coordinates

  {

    lcd.setCursor(0,0);
    lcd.print("Go ");

    float fDist = (double)calc_dist(flat, flon, targetFlat, targetFlon) / 1000;

    float avgSpeed = 0;

    float fDist2 = distance;
    fDist2 /= 1000;

    if (hours != 0)
      avgSpeed = fDist2 / hours;

    printLCDFloat(fDist, 3);

    lcd.print("km");

    lcd.setCursor(0, 1);

    if (useDirections == 0) {
      if (useAbsoluteHeadings == 1) {
        if (calc_bearing(flat, flon, targetFlat, targetFlon) < 99.5)
          lcd.print(" ");
        if (calc_bearing(flat, flon, targetFlat, targetFlon) < 9.5)
          lcd.print(" ");
        printLCDFloat(calc_bearing(flat, flon, targetFlat, targetFlon), 0);
        lcd.write(2);
        lcd.print(" T");
      }
      else {
        if ((calc_bearing(flat, flon, targetFlat, targetFlon) - gps.f_course()) > 0) {
          if (calc_bearing(flat, flon, targetFlat, targetFlon)-gps.f_course() < 99.5)
            lcd.print(" ");
          if (calc_bearing(flat, flon, targetFlat, targetFlon)-gps.f_course() < 9.5)
            lcd.print(" ");
          printLCDFloat(calc_bearing(flat, flon, targetFlat, targetFlon)-gps.f_course(), 0);
          lcd.write(2);
          lcd.print(" R");
        }
        else {
          if (calc_bearing(flat, flon, targetFlat, targetFlon)-gps.f_course()+360 < 99.5)
            lcd.print(" ");
          if (calc_bearing(flat, flon, targetFlat, targetFlon)-gps.f_course()+360 < 9.5)
            lcd.print(" ");
          printLCDFloat(calc_bearing(flat, flon, targetFlat, targetFlon)-gps.f_course()+360, 0);
          lcd.write(2);
          lcd.print(" R");
        }
      }
      lcd.print("  ");
    }
    else {
      if (useAbsoluteHeadings == 1) {
        printHeadingDirection(calc_bearing(flat, flon, targetFlat, targetFlon));
        lcd.print(" T");
      }
      else {
        if ((calc_bearing(flat, flon, targetFlat, targetFlon) - gps.f_course()) > 0) {
          printHeadingDirection(calc_bearing(flat, flon, targetFlat, targetFlon)-gps.f_course());
          lcd.print(" R");
        }
        else {
          printHeadingDirection(calc_bearing(flat, flon, targetFlat, targetFlon)-gps.f_course()+360);
          lcd.print(" R");
        }
      }
    }

    lcd.setCursor(8, 1);

    long ETA = 0;

    if (useCurrentSpeed == 1)
    {
      if (gps.f_speed_kmph() != 0)
        ETA = (fDist/gps.f_speed_kmph())*60*60;
    }
    else
    {
      if (avgSpeed != 0)
        ETA = ((double)fDist/(double)avgSpeed)*60*60;
    }

    if (ETA/60/60 < 10)
      lcd.print("0");

    if (ETA/60/60 < 100)  // limit display to 99 hours
      printLCDFloat((ETA/60/60)%100, 0);

    int ETAHours = ETA/60/60;

    lcd.print(":");

    if ((ETA/60-(ETAHours*60) < 10))
      lcd.print("0");
    printLCDFloat((ETA/60-(ETAHours*60)), 0);

    int ETAMinutes = (ETA/60);

    lcd.print(":");

    if ((ETA-(ETAMinutes*60) < 10))
      lcd.print("0");
    printLCDFloat((ETA-(ETAMinutes*60)), 0);

  }

  if (screen == 5)  // Date and Time

  {

    int timeIZone;

    if (timeZone <= 12)
      timeIZone = (int)timeZone;
    else
      timeIZone = ((int)timeZone - 12) * - 1;

    int ihour = (int)hour + timeIZone;

    if (ihour > 23) {
      ihour = ihour - 24;
      day = day - 1;
    }

    if (ihour < 0) {
      ihour = ihour + 24;
      day = day - 1;
    }

    lcd.setCursor(0, 0);
    lcd.print("Date ");
    printLCDFloat(year, 0);
    lcd.print("/");
    if (month < 10)
      lcd.print("0");
    printLCDFloat(month, 0);
    lcd.print("/");
    if (day < 10)
      lcd.print("0");
    printLCDFloat(day, 0);
    lcd.setCursor(0, 1);
    lcd.print("Time ");
    if (ihour < 10)
      lcd.print("0");
    printLCDFloat(ihour, 0);
    lcd.print(":");
    if (minute < 10)
      lcd.print("0");
    printLCDFloat(minute, 0);
    lcd.print(":");
    if (second < 10)
      lcd.print("0");
    printLCDFloat(second, 0);

  }
  
  if (age > 30000)
   {
     delay(3000);
   }

}


void showNavigationMenu() {
 
 boolean inMenu = 0;
 byte lastOption = 1;
 byte option = 0;

  while (inMenu == 0) {
    
     if ((option == 0)&&(lastOption != 0))
    {
      lcd.clear();
      lcd.print("  Mark as");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" waypoint");
      lastOption = 0;
    }
    
    if ((option == 1)&&(lastOption != 1))
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Return to");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" main menu");
      lastOption = 1;
    }
    
    if ((option == 2)&&(lastOption != 2))
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Cancel");
      lastOption = 2;
    }
    
    switch (getKeyDebounce())
    {

    case 1:
      if (option != 0)
        option--;
      break;
    case 2:
      if (option != 2)
        option++;
      break;
    case 4:
      if (option == 1) {
        showMenu(); }
      else if (screen == 0) {
        selectWaypoint();
        saveWaypoint(lastFlat, lastFlon);
        editWaypointName(); 
        lcd.clear(); }
      inMenu = 1;
      break;
      
    }
    
  }

}
  

void showMenu() {

  boolean inMenu = 0;

//  lcd.clear();
//  lcd.print("Please select");
//  lcd.setCursor(5, 1);
//  lcd.print("mode");

//  delay(2000);

  while (inMenu == 0)
  {
    
    // Main menu
    
    if (screen == 0) // Coordinates heading, speed
    {
      lcd.clear();
      lcd.print("  Coordinates,");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" heading, speed");
    }
    if (screen == 1) // Distance avg/max speed
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Distance,");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" avg/max speed");
    }
    if (screen == 2) // Navigate to coordinates
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Navigate to");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" coordinates");
    }
    if (screen == 3) // Navigate to waypoint
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Navigate to");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" waypoint");
    }
    if (screen == 4) // View & edit waypoints
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" View & edit");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" waypoints");
    }
    if (screen == 5) // Date & time
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Date & time");
      lcd.setCursor(0,1);
      lcd.write(1);
    }
    if (screen == 6) // Options
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Options");
    }
    
    // Options menu
    
    if (screen == 10) // Current vs average speed to get ETA
    {
      lcd.clear();
      if (useCurrentSpeed == 1)
        lcd.print("  Current speed");
      else
        lcd.print("  Average speed");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" to get ETA");
    }
    if (screen == 11) // Show headings as number vs letters
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Show headings");
      lcd.setCursor(0,1);
      lcd.write(1);
      if (useDirections == 0) {
        lcd.print(" as 353");
        lcd.write(2);
      }
      else
        lcd.print(" as NNW");
    }
    if (screen == 12) // Show headings as absolute vs relative
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Show headings");
      lcd.setCursor(0,1);
      lcd.write(1);
      if (useAbsoluteHeadings == 1)
        lcd.print(" as absolute");
      else
        lcd.print(" as relative");
    }
    if (screen == 13) // Set time zone
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Time zone");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" GMT ");
      int timeIZone;
      if (timeZone <= 12)
        timeIZone = (int)timeZone;
      else
        timeIZone = ((int)timeZone - 12) * - 1;
      printLCDFloat(timeIZone, 0);
    }
    if (screen == 15)
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Delete all");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" waypoints");
    }
    if (screen == 14)
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Backup");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" waypoints");
    }
    if (screen == 16)
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Return to");
      lcd.setCursor(0,1);
      lcd.print("  main menu");
    }
    
    // Reset menu
    
    if (screen == 20)
    {
      lcd.clear();
      lcd.print("  Are you sure?");
      lcd.setCursor(0,1);
      lcd.write(1);
      lcd.print(" No!");
    }
    if (screen == 21)
    {
      lcd.clear();
      lcd.write(0);
      lcd.print(" Are you sure?");
      lcd.setCursor(0,1);
      lcd.print("  Yes!");
    }

    switch (getKeyDebounce())
    {

    case 1:
      if ((screen != 0)&&(screen != 10)&&(screen != 20))
        screen--;
      break;
    case 2:
      if ((screen != 6)&&(screen != 16)&&(screen != 21))
        screen++;
      break;
    case 4:
    
      // Main menu
    
      if (screen == 2) // Navigate to coordinates
      {
        setTargetCoords();
        inMenu = 1;
      }
      else if (screen == 3) // Navigate to waypoint
      {
        selectWaypoint();
        printTargetCoords();
        delay(2000);
        inMenu = 1;
      }
      else if (screen == 4) // View & edit waypoints
      {
        selectWaypoint();
        editWaypointName();
        setTargetCoords();
        saveWaypoint(targetFlat, targetFlon);
      }
      else if (screen == 6) // Options
      {
        screen = 10;
      }
      
      // Options menu
      
      else if (screen == 14) // Backup
      {
        saveEEPROM();
      }
      else if (screen == 15) // Reset menu
      {
        screen = 20;
      }
      else if (screen == 16) // Exit options menu
      {
        screen = 6;
      }
      
      // Reset menu
      
      else if (screen == 20) // Exit reset menu
      {
        screen = 15;
      }
      else if (screen == 21) // Reset device
      {
        clearEEPROM();
        screen = 15;
      }
        
      
      else if ((screen == 0)||(screen == 1)||(screen == 2)||(screen == 3)||(screen == 5)) // Enter the main loop
      {
        inMenu = 1;
      }
      
      break;
      
    case 0:
    
      // Options menu
    
      if (screen == 10) {
        if (useCurrentSpeed == 0)
          useCurrentSpeed = 1;
        else
          useCurrentSpeed = 0;
        EEPROM.write(0,(byte)useCurrentSpeed);
      }
      if (screen == 11) {
        if (useDirections == 0)
          useDirections = 1;
        else
          useDirections = 0;
        EEPROM.write(1,(byte)useDirections);
      }
      if (screen == 12) {
        if (useAbsoluteHeadings == 0)
          useAbsoluteHeadings = 1;
        else
          useAbsoluteHeadings = 0;
        EEPROM.write(2,(byte)useAbsoluteHeadings);
      }
      if (screen == 13) {
        timeZone = timeZone + 1;
        if (timeZone == 25)
          timeZone = 0;
        EEPROM.write(3,(byte)timeZone);
      }
      break;
      
    case 3:
    
      // Options menu
    
      if (screen == 10) {
        if (useCurrentSpeed == 0)
          useCurrentSpeed = 1;
        else
          useCurrentSpeed = 0;
        EEPROM.write(0,(byte)useCurrentSpeed);
      }
      if (screen == 11) {
        if (useDirections == 0)
          useDirections = 1;
        else
          useDirections = 0;
        EEPROM.write(1,(byte)useDirections);
      }
      if (screen == 12) {
        if (useAbsoluteHeadings == 0)
          useAbsoluteHeadings = 1;
        else
          useAbsoluteHeadings = 0;
        EEPROM.write(2,(byte)useAbsoluteHeadings);
      }
      if (screen == 13) {
        timeZone = timeZone - 1;
        if (timeZone == 255)  // This is a byte so negative values will wrap back to 255
            timeZone = 24;
        EEPROM.write(3,(byte)timeZone);
      }
      break;

    }

  }

  lcd.clear();
  lcd.print("Acquiring");
  lcd.setCursor(5, 1);
  lcd.print("signal...");

  screenRefresh = 120;

}


void selectWaypoint() {
  
  lcd.clear();
  lcd.print("Select a");
  lcd.setCursor(5, 1);
  lcd.print("waypoint...");
  
  delay(2000);
  
  boolean inMenu = 0;
  
  while (inMenu == 0) {
    
    lcd.clear();
    if (waypoint != 1)
      lcd.write(0);
    else
      lcd.print(" ");
    lcd.print(" Waypoint #");
    printLCDFloat(waypoint, 0);
    lcd.setCursor(0, 1);
    if (waypoint != 20)
      lcd.write(1);
    else
      lcd.print(" ");
    lcd.print(" ");
    for (int i = 0; i < 14; i++)
      lcd.print((char)EEPROM.read((waypoint * 22) + 8 + i));
    
    switch (getKeyDebounce())
    {
    case 1:
      if (waypoint != 1)
        waypoint--;
      break;
    case 2:
      if (waypoint != 20)
        waypoint++;
      break;
    case 4:
      inMenu = 1;
    break;
    }
      
  }
  
  bitFloat loadFloat;
  
  loadFloat.byte[0] = EEPROM.read((22 * waypoint) + 0);
  loadFloat.byte[1] = EEPROM.read((22 * waypoint) + 1);
  loadFloat.byte[2] = EEPROM.read((22 * waypoint) + 2);
  loadFloat.byte[3] = EEPROM.read((22 * waypoint) + 3);
  targetFlat = loadFloat.float_num;
  
  loadFloat.byte[0] = EEPROM.read((22 * waypoint) + 4);
  loadFloat.byte[1] = EEPROM.read((22 * waypoint) + 5);
  loadFloat.byte[2] = EEPROM.read((22 * waypoint) + 6);
  loadFloat.byte[3] = EEPROM.read((22 * waypoint) + 7);
  targetFlon = loadFloat.float_num;
  
}


void saveWaypoint(float saveLat, float saveLon) {
  
  bitFloat saveFloat;
  
  saveFloat.float_num = saveLat;
  EEPROM.write((22 * waypoint) + 0, saveFloat.byte[0]);
  EEPROM.write((22 * waypoint) + 1, saveFloat.byte[1]);
  EEPROM.write((22 * waypoint) + 2, saveFloat.byte[2]);
  EEPROM.write((22 * waypoint) + 3, saveFloat.byte[3]);
  
  saveFloat.float_num = saveLon;
  EEPROM.write((22 * waypoint) + 4, saveFloat.byte[0]);
  EEPROM.write((22 * waypoint) + 5, saveFloat.byte[1]);
  EEPROM.write((22 * waypoint) + 6, saveFloat.byte[2]);
  EEPROM.write((22 * waypoint) + 7, saveFloat.byte[3]);  
  
}


void editWaypointName() {
 
 byte cursorPosition = 1; 
 lcd.blink();
 boolean updated = 1;
 boolean inMenu = 0;

  while (inMenu == 0)
  {

      lcd.clear();
      lcd.print("Waypoint name:");
      lcd.setCursor(0,1);
      for (int i = 0; i < 14; i++) {
        char printLetter;
        printLetter = EEPROM.read(((waypoint * 22) + 8 + i));
        lcd.print(printLetter);
      }
        
      switch (cursorPosition)
      {
      case 1:
        lcd.setCursor(0, 1);
        break;
      case 2:
        lcd.setCursor(1,1);
        break;
      case 3:
        lcd.setCursor(2,1);
        break;
      case 4:
        lcd.setCursor(3,1);
        break;
      case 5:
        lcd.setCursor(4,1);
        break;
      case 6:
        lcd.setCursor(5,1);
        break;
      case 7:
        lcd.setCursor(6,1);
        break;
      case 8:
        lcd.setCursor(7,1);
        break;
      case 9:
        lcd.setCursor(8,1);
        break;
      case 10:
        lcd.setCursor(9,1);
        break;
      case 11:
        lcd.setCursor(10,1);
        break;
      case 12:
        lcd.setCursor(11,1);
        break;
      case 13:
        lcd.setCursor(12,1);
        break;
      case 14:
        lcd.setCursor(13,1);
        break;
      }
    
  switch (getKeyDebounce())
  {

    case 1: {
      byte letter = EEPROM.read((waypoint * 22) + 7 + cursorPosition);
      letter++;
      if (letter >= 91)
        letter = 48;
      if (letter == 33)
        letter = 65;
      if (letter == 58)
        letter = 32;
      EEPROM.write((waypoint * 22) + 7 + cursorPosition, letter);  
      break; }
    case 2: {
      byte letter = EEPROM.read((waypoint * 22) + 7 + cursorPosition);
      letter--;
      if (letter == 64)
        letter = 32;
      if (letter == 47)
        letter = 90;
      if (letter <= 31)
        letter = 57;
      EEPROM.write((waypoint * 22) + 7 + cursorPosition, letter);
      break; }
    case 0: {
      cursorPosition++;
      if (cursorPosition > 14)
        cursorPosition = 1;
      break; }
    case 3: {
      cursorPosition--;
      if (cursorPosition < 0)
        cursorPosition = 14;
      break; }
    case 4: {
      inMenu = 1;
      lcd.noBlink();
      break; }
    
  }
  
  }
  
}


void printTargetCoords() {
  
   lcd.clear();
      if (targetFlat > 0)
      {
        lcd.print("(N) + ");
        if (targetFlat < 10)
          lcd.print("0");
        printLCDFloat(targetFlat, 5);
      }
      else
      {
        lcd.print("(S) - ");
        if (targetFlat > -10)
          lcd.print("0");
        printLCDFloat(targetFlat*-1, 5);
      }
      lcd.setCursor(0,1);
      if (targetFlon > 0) 
      {
        lcd.print("(E) +");
        if (targetFlon < 100)
          lcd.print("0");
        if (targetFlon < 10)
          lcd.print("0");
        printLCDFloat(targetFlon, 5);
      }
      else
      {
        lcd.print("(W) -");
        if (targetFlon > -100)
          lcd.print("0");
        if (targetFlon > -10)
          lcd.print("0");
        printLCDFloat(targetFlon*-1, 5);
      }
      
}



void setTargetCoords() {

  boolean inMenu = 0;
  boolean updated = 1;
  byte cursorPosition = 1;

  lcd.clear();
  lcd.print("Please enter");
  lcd.setCursor(5, 1);
  lcd.print("coordinates");

  delay(2000);

  lcd.blink();

  while (inMenu == 0)
  {

    if (updated == 1)
    {
      
      printTargetCoords();

      switch (cursorPosition)
      {
      case 1:
        lcd.setCursor(1, 0);
        break;
      case 2:
        lcd.setCursor(4,0);
        break;
      case 3:
        lcd.setCursor(6,0);
        break;
      case 4:
        lcd.setCursor(7,0);
        break;
      case 5:
        lcd.setCursor(9,0);
        break;
      case 6:
        lcd.setCursor(10,0);
        break;
      case 7:
        lcd.setCursor(11,0);
        break;
      case 8:
        lcd.setCursor(12,0);
        break;
      case 9:
        lcd.setCursor(13,0);
        break;
      case 10:
        lcd.setCursor(1,1);
        break;
      case 11:
        lcd.setCursor(4,1);
        break;
      case 12:
        lcd.setCursor(5,1);
        break;
      case 13:
        lcd.setCursor(6,1);
        break;
      case 14:
        lcd.setCursor(7,1);
        break;
      case 15:
        lcd.setCursor(9,1);
        break;
      case 16:
        lcd.setCursor(10,1);
        break;
      case 17:
        lcd.setCursor(11,1);
        break;
      case 18:
        lcd.setCursor(12,1);
        break;
      case 19:
        lcd.setCursor(13,1);
        break;
      } 

      updated = 0;
    }

    switch (getKeyDebounce())
    {
    case 0:
      cursorPosition++;
      if (cursorPosition == 20)
        cursorPosition = 1;
      updated = 1;
      break;
    case 3:
      cursorPosition--;
      if (cursorPosition == 0)
        cursorPosition = 19;
      updated = 1;
      break;
    case 1:
      switch (cursorPosition)
      {
      case 1:
        targetFlat *= -1;
        break;
      case 2:
        targetFlat *= -1;
        break;
      case 3:
        targetFlat += 10;
        break;
      case 4:
        targetFlat += 1;
        break;
      case 5:
        targetFlat += .1;
        break;
      case 6:
        targetFlat += .01;
        break;
      case 7:
        targetFlat += .001;
        break;
      case 8:
        targetFlat += .0001;
        break;
      case 9:
        targetFlat += .00001;
        break;
      case 10:
        targetFlon *= -1;
        break;
      case 11:
        targetFlon *= -1;
        break;
      case 12:
        targetFlon += 100;
        break;
      case 13:
        targetFlon += 10;
        break;
      case 14:
        targetFlon += 1;
        break;
      case 15:
        targetFlon += .1;
        break;
      case 16:
        targetFlon += .01;
        break;
      case 17:
        targetFlon += .001;
        break;
      case 18:
        targetFlon += .0001;
        break;
      case 19:
        targetFlon += .00001;
        break;
      }
      updated = 1;
      break;
    case 2:
      switch (cursorPosition)
      {
      case 1:
        targetFlat *= -1;
        break;
      case 2:
        targetFlat *= -1;
        break;
      case 3:
        targetFlat -= 10;
        break;
      case 4:
        targetFlat -= 1;
        break;
      case 5:
        targetFlat -= .1;
        break;
      case 6:
        targetFlat -= .01;
        break;
      case 7:
        targetFlat -= .001;
        break;
      case 8:
        targetFlat -= .0001;
        break;
      case 9:
        targetFlat -= .00001;
        break;
      case 10:
        targetFlon *= -1;
        break;
      case 11:
        targetFlon *= -1;
        break;
      case 12:
        targetFlon -= 100;
        break;
      case 13:
        targetFlon -= 10;
        break;
      case 14:
        targetFlon -= 1;
        break;
      case 15:
        targetFlon -= .1;
        break;
      case 16:
        targetFlon -= .01;
        break;
      case 17:
        targetFlon -= .001;
        break;
      case 18:
        targetFlon -= .0001;
        break;
      case 19:
        targetFlon -= .00001;
        break;
      }
      updated = 1;
      break;
    case 4:
      inMenu = 1;
      lcd.noBlink();
      break;
    }

  }

  printFloat(targetFlat,5);
  printFloat(targetFlon,5);

}



void showSplash() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Arduino GPS");
  lcd.setCursor(5, 1);
  lcd.print("Version 2.0");

  delay(3000);



}

bool feedgps()
{
  while (nss.available())
  {
    if (gps.encode(nss.read()))
      return true;
  }
  return false;
}


void printHeadingDirection(float heading) {

  if ((heading > 348.75)||(heading < 11.25))
    lcd.print("  N");
  if ((heading >= 11.25)&&(heading < 33.75))
    lcd.print("NNE");
  if ((heading >= 33.75)&&(heading < 56.25))
    lcd.print(" NE");
  if ((heading >= 56.25)&&(heading < 78.75))
    lcd.print("ENE");
  if ((heading >= 78.75)&&(heading < 101.25))
    lcd.print("  E");
  if ((heading >= 101.25)&&(heading < 123.75))
    lcd.print("ESE");
  if ((heading >= 123.75)&&(heading < 146.25))
    lcd.print(" SE");
  if ((heading >= 146.25)&&(heading < 168.75))
    lcd.print("SSE");
  if ((heading >= 168.75)&&(heading < 191.25))
    lcd.print("  S");
  if ((heading >= 191.25)&&(heading < 213.75))
    lcd.print("SSW");
  if ((heading >= 213.75)&&(heading < 236.25))
    lcd.print(" SW");
  if ((heading >= 236.25)&&(heading < 258.75))
    lcd.print("WSW");
  if ((heading >= 258.75)&&(heading < 281.25))
    lcd.print("  W");
  if ((heading >= 281.25)&&(heading < 303.75))
    lcd.print("WNW");
  if ((heading >= 303.75)&&(heading < 326.25))
    lcd.print(" NW");
  if ((heading >= 326.25)&&(heading < 348.75))
    lcd.print("NWN");

}


int calc_bearing(float flat1, float flon1, float flat2, float flon2)
{
  float calc;
  float bear_calc;

  float x = 69.1 * (flat2 - flat1); 
  float y = 69.1 * (flon2 - flon1) * cos(flat1/57.3);

  calc=atan2(y,x);

  bear_calc= degrees(calc);

  if(bear_calc<=1){
    bear_calc=360+bear_calc; 
  }
  return bear_calc;
}  

unsigned long calc_dist(float flat1, float flon1, float flat2, float flon2)
{
  float dist_calc=0;
  float dist_calc2=0;
  float diflat=0;
  float diflon=0;

  //I've to spplit all the calculation in several steps. If i try to do it in a single line the arduino will explode.
  diflat=radians(flat2-flat1);
  flat1=radians(flat1);
  flat2=radians(flat2);
  diflon=radians((flon2)-(flon1));

  dist_calc = (sin(diflat/2.0)*sin(diflat/2.0));
  dist_calc2= cos(flat1);
  dist_calc2*=cos(flat2);
  dist_calc2*=sin(diflon/2.0);
  dist_calc2*=sin(diflon/2.0);
  dist_calc +=dist_calc2;

  dist_calc=(2*atan2(sqrt(dist_calc),sqrt(1.0-dist_calc)));

  dist_calc*=6371000.0; //Converting to meters, i love the metric system.. =)
  return dist_calc;
}


void clearEEPROM()
{
  lcd.clear();
  lcd.print("Formating EEPROM");
  lcd.setCursor(2,1);
  lcd.print("[");
  lcd.setCursor(13,1);
  lcd.print("]");
  
  delay(2000);
  
  bitFloat lat;
  lat.float_num = 49.88622; //Default value for waypoints
  bitFloat lon;
  lon.float_num = -97.15256; //Default value for waypoints

  for (int i = 1; i < 21; i++) {
  
    EEPROM.write((22 * i) + 0, lat.byte[0]);
    EEPROM.write((22 * i) + 1, lat.byte[1]);
    EEPROM.write((22 * i) + 2, lat.byte[2]);
    EEPROM.write((22 * i) + 3, lat.byte[3]);
  
    EEPROM.write((22 * i) + 4, lon.byte[0]);
    EEPROM.write((22 * i) + 5, lon.byte[1]);
    EEPROM.write((22 * i) + 6, lon.byte[2]);
    EEPROM.write((22 * i) + 7, lon.byte[3]);
  
    for (int x = 1; x < 15; x++)
      EEPROM.write((22 * i) + 7 + x, char(' '));
      
    lcd.setCursor(((i+1)/2)+2,1);
    lcd.print("-");
  }
  
  lcd.setCursor(6,1);
  lcd.print("DONE");
  
  delay(3000);
 
}


void saveEEPROM()
{
  
  lcd.clear();
  lcd.print("Start serial");
  lcd.setCursor(0, 1);
  lcd.print("monitor @ 57600");

  delay(5000);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Dumping EEPROM");
  lcd.setCursor(2,1);
  lcd.print("[");
  lcd.setCursor(13,1);
  lcd.print("]");
  
  delay(2000);
  
  Serial.println("#include <EEPROM.h>");
  Serial.println("#include <LiquidCrystal.h>");
  Serial.println("LiquidCrystal lcd(8, 9, 4, 5, 6, 7);");
  Serial.println("void setup() {");
  
  Serial.println("lcd.begin(16, 2);");
  Serial.println("lcd.clear();");
  Serial.println("lcd.setCursor(1,0);");
  Serial.println("lcd.print(\"Loading EEPROM\");");
  Serial.println("lcd.setCursor(2,1);");
  Serial.println("lcd.print(\"[   BUSY   ]\");");
  
  for (int i = 0; i < 1024; i++)
  {  
    Serial.print("EEPROM.write(");
    Serial.print(i);
    Serial.print(",");
    Serial.print(int(EEPROM.read(i)));
    Serial.println(");");
    
    lcd.setCursor(((i)/103)+3,1);
    lcd.print("-");
  }
  
  Serial.println("lcd.setCursor(6,1);");
  Serial.println("lcd.print(\"DONE\");");
  
  Serial.println("}");
  Serial.println("void loop() {");
  Serial.println("}");
  
  lcd.setCursor(6,1);
  lcd.print("DONE");
  
  delay(3000);
  
}

