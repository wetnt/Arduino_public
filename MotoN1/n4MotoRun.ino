int mas = 10;
int maa = 12;
int mab = 13;
int mbs = 9;
int mba = 8;
int mbb = 11;
int sfr = 7;
int sfc = 6;
int sfl = 5;

void motor_r(int s)
{
  if (s == 0)
  {
    digitalWrite(maa, LOW);
    digitalWrite(mab, LOW);
    digitalWrite(mas, HIGH);
  }
  else if ( 0 < s && s < 256)
  {
    digitalWrite(maa, HIGH);
    digitalWrite(mab, LOW);
    analogWrite(mas, s);
    delay(20);
  }
  else if ( 0 > s && s > -256)
  {
    digitalWrite(maa, LOW);
    digitalWrite(mab, HIGH);
    analogWrite(mas, -s);
    delay(20);
  }
  else digitalWrite(mas, LOW);
}
void motor_l(int s)
{
  if (s == 0)
  {
    digitalWrite(mba, LOW);
    digitalWrite(mbb, LOW);
    digitalWrite(mbs, HIGH);
  }
  else if (s > 0 && s < 256)
  {
    digitalWrite(mba, HIGH);
    digitalWrite(mbb, LOW);
    analogWrite(mbs, s);
    delay(20);
  }
  else if (s < 0 && s > -256)
  {
    digitalWrite(mba, LOW);
    digitalWrite(mbb, HIGH);
    analogWrite(mbs, -s);
    delay(20);
  }
  else digitalWrite(mbs, LOW);
}
