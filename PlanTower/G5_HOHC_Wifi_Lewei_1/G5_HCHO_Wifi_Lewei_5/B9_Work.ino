//=====================================================
int Work_Secend = 15;
unsigned long Work_Time = millis();
void Work_Loop() {
  if (millis() - Work_Time < Work_Secend * 1000) return;
  Work_Time = millis(); Work_Loop_Run();
}
//=====================================================
void Work_Loop_Run() {
  //lg(F("------------------------------------")); lg();
  G5_Show(); ShowHCHO(); Si7021_show();
  //lg(F("------------------------------------")); lg();
  Lewei_Loop();
}
//=====================================================
