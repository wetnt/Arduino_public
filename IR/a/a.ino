//=========================================
void setup()
{
  Serial.begin(115200);
  Serial.println("testabc"); 
  IR_Setup(4,5,6);
}
//=========================================
void loop()
{
  IR_Loop();
  IR_Show(true);
}
//=========================================


