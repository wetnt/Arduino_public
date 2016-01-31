//=================================================================
int range = 100;               // output range of X or Y movement
int threshold = range/20;      // resting threshold
int center = range/2;         // resting position value
//=================================================================
int readAxis(int thisAxis) { 
  int reading = analogRead(thisAxis);
  reading = map(reading, 0, 1023, 0, range);
  int distance = reading - center;
  if (abs(distance) < threshold) {
    distance = 0;
  } 
  return distance;
}
//=================================================================
int readDigital(int thisAxis) { 
  //-------------------------------------------- 
  int reading = digitalRead(thisAxis);
  //-------------------------------------------- 
  if(reading != 1)
    reading = 1;
  else
    reading = 0;
  //-------------------------------------------- 
  return reading;
  //-------------------------------------------- 
}

