//=================================================================
int range = 255;               // output range of X or Y movement
int threshold = range / 20;    // resting threshold
int center = range / 2;       // resting position value
//=================================================================
int readAxis(int thisAxis) {
  int reading = analogRead(thisAxis);
  reading = map(reading, 0, 1023, 0, range);
  return reading;
}
int readAxis2(int thisAxis) {
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
  if (reading != 1)
    reading = 1;
  else
    reading = 0;
  //--------------------------------------------
  return reading;
  //--------------------------------------------
}


int GetCenterMapValue(int tValue, int midValue) {
  if (tValue == midValue) {
    tValue = center;
  } else if (tValue > midValue) {
    tValue = map(tValue, midValue, range, center, range);
  } else if (tValue < midValue) {
    tValue = map(tValue, 0, midValue, 0, center);
  }
  return tValue;
}
