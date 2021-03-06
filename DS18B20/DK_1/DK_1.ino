//--------------------------------------------
int ledPin = 13;
//--------------------------------------------
void setup(void)
{
  //--------------------------------------------
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  //--------------------------------------------
  DS18B20_setup();
  DS18B20_setup_print();
  //--------------------------------------------
}

void loop(void)
{
  //--------------------------------------------
  DS18B20_loop();
  DS18B20_loop_print();
  //--------------------------------------------
  if ( DS18B20_Key() ){
    Blink_Flash(ledPin);
    Blink_Flash(ledPin);
    Blink_Flash(ledPin);
  }
  //--------------------------------------------
  delay(5000);
  //--------------------------------------------
}

