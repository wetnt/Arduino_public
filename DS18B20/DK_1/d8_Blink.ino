void Blink_loop()
{
  //--------------------------------------------
  if ( DS18B20_Key() )
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  //--------------------------------------------
}

void Blink_Flash(int ledPin)
{
  //--------------------------------------------
  digitalWrite(ledPin, HIGH);
  delay(50);
  digitalWrite(ledPin, LOW);
  delay(50);
  //--------------------------------------------
}


