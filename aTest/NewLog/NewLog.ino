static const String codeName = "Mpu6050_Nano_WS201X_2";
//===================================================================
void setup() {
  lg_setup(codeName,"abc",false,'{','}');  
}
void loop() {
  lg_loop();  
}
