void SerialShow(){
  //-----------------------------------------------------------
  Serial.println("------------------------");
  Serial.print("Voltage = ");  Serial.println(Volt,DEC);
  Serial.print("Amp     = ");  Serial.println(Amps,DEC);
  Serial.print("Watt    = ");  Serial.println(Watt,DEC);
  Serial.print("Kwh     = ");  Serial.println(Kwhs,DEC);
  Serial.print("Pf      = ");  Serial.println(Pfss,DEC);
  Serial.print("Cabon   = ");  Serial.println(Cabn,DEC);
  //-----------------------------------------------------------
}
