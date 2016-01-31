//====================================
const int numReadings = 20;
//====================================
int readings[numReadings]; 
int index = 0;
int total = 0;
int average = 0;
//====================================
int ledssPin = 13;
int inputPin = A0;
//====================================
int maxa = 50;
int maxb = 50;
//====================================

void setup()
{
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(ledssPin,OUTPUT);

  for (int i = 0; i < numReadings; i++)
    readings[i] = 0;
}

void loop(){
  readRun();
}

void readRun(){
  //-------------------------------------------- 
  total = total - readings[index];
  readings[index] = analogRead(inputPin); 
  total = total + readings[index];
  //-------------------------------------------- 
  index++; 
  if(index >= numReadings){
    index = 0;
  }
  //--------------------------------------------  
  average = total / numReadings;
  average = average / 10;
  //--------------------------------------------  
  if(maxa>average) maxa = average;
  if(maxb<average) maxb = average;
  //-------------------------------------------- 
  //analogWrite(ledssPin, average);
  //-------------------------------------------- 
  int val = map(average, maxa, maxb, -255, 255);
  Serial.print(maxa, DEC);
  Serial.print(" ");
  Serial.print(average, DEC);
  Serial.print(" ");
  Serial.print(maxb, DEC); 
  Serial.print(" ");
  Serial.println(val, DEC); 
  //--------------------------------------------  

  //--------------------------------------------  
}

