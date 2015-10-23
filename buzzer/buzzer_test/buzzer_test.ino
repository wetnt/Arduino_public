int buzzer = 6;
void setup()
{
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  
  voice_b();
}

void loop ()
{
//  delay(2000);
//  voice_a();
//  delay(2000);
//  voice_b();
//  delay(2000);
//  voice_c();
//  delay(15000);
}


void voice_a() {
  digitalWrite(buzzer, HIGH);
  delay(1);
  digitalWrite(buzzer, LOW); //音
  delay(1);
}

void voice_b() {
  for (int i = 0; i < 100; i++)
  {
    digitalWrite(buzzer, HIGH);
    delay(2);
    digitalWrite(buzzer, LOW);
    delay(2);
  }
}

void voice_c() {
  for (int i = 0; i < 80; i++)
  {
    digitalWrite(buzzer, HIGH);
    delay(1);
    digitalWrite(buzzer, LOW); //音
    delay(1);
  }
}
