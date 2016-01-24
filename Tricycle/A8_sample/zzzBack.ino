

//---------------------------------------------------------
// MotorRunAB(0, 0); Interrupt_clear();
// lg("SpeedMaxR="); lg(SpeedMaxR); lg();
//---------------------------------------------------------
void Car_Speed_level() { //运行速度初始化
  //---------------------------------------------------------
  lg("Car_Get_Speed_level():"); lg(loopms); lg("ms"); lg();
  //---------------------------------------------------------
  SpeedMaxR = 0; CarStartR = 0;
  for (int i = 0; i < 256; i++) {
    MotorRunAB(i, 0); smartDelay(loopms);
    rSpeed = 22.5 * intR / loopms; Interrupt_clear();
    if (rSpeed > 0 && CarStartR == 0) CarStartR = i;
    if (SpeedMaxR < rSpeed) SpeedMaxR = rSpeed;
  }
  //---------------------------------------------------------
  lg("CarStartR="); lg(CarStartR); lg(" ");
  lg("SpeedMaxR="); lg(SpeedMaxR); lg();
  //---------------------------------------------------------
  MotorRunAB(0, 0); smartDelay(1000); Interrupt_clear();
  //---------------------------------------------------------
  SpeedMaxR = 0; CarStartR = 0;
  for (int i = 255; i > 0; i--) {
    MotorRunAB(i, 0); smartDelay(loopms);
    rSpeed = 22.5 * intR / loopms; Interrupt_clear();
    if (rSpeed <= 0  && CarStartR == 0) CarStartR = i;
    if (SpeedMaxR < rSpeed) SpeedMaxR = rSpeed;
  }
  //MotoRunAB( 1000,  0); smartDelay(500);
  //MotoRunAB(-1000, -1000); smartDelay(1000);
  //MotoRunAB(0, 0); smartDelay(1000);
  //---------------------------------------------------------
  lg("CarStartR="); lg(CarStartR); lg(" ");
  lg("SpeedMaxR="); lg(SpeedMaxR); lg();
  //---------------------------------------------------------
}
