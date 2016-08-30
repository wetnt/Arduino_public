//TB6612

int PWMA = 3;
int AIN1 = 7;
int AIN2 = 8;
 
int PWMB = 5;
int BIN1 = 10;
int BIN2 = 11;
 
int STBY = 4;
 
int pinLed = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  Serial.begin(115200);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  char readChar;
  while (Serial.available() > 0) //read the betys from the serial buffer
  {
    readChar = Serial.read();
    if (readChar == 'Y' || readChar == 'y') // always light the led onboard
    {
      digitalWrite(pinLed, HIGH);
      for (int i = 0; i < 48; i++)
      {
        driveStepper();
      }
      Serial.println("read Y");
    }
    else if (readChar == 'S' || readChar == 's')// blink the led onborad
    {
      digitalWrite(pinLed, LOW);
      delay(100);
      digitalWrite(pinLed, HIGH);
      delay(100);
      digitalWrite(pinLed, LOW);
      delay(100);
      digitalWrite(pinLed, HIGH);
      delay(100);
      digitalWrite(pinLed, LOW);
      Serial.println("read s");
      stopStepper();
    }
    Serial.println(readChar);
    delay(100);
  }
}
 
void stopStepper()
{
  digitalWrite(STBY, LOW);
}
 
void stepStepper()
{
  digitalWrite(STBY, HIGH);
  for (int i = 0; i < 4; i++)
  {
    delay(10);
    if (i == 0)
    {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
    }
    else if (i == 1)
    {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
    }
    else if (i == 2)
    {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    }
    else if (i == 3)
    {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    }
  }
}
 
void driveStepper()
{
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
  stepStepper();
}

