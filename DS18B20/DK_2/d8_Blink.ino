//===============================================
void Blink_Flash(int ledPin)
{
  //--------------------------------------------
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  digitalWrite(ledPin, LOW);
  //--------------------------------------------
}
void Blink_Stop(int ledPin)
{
  //--------------------------------------------
  digitalWrite(ledPin, LOW);
  //--------------------------------------------
}
//===============================================


