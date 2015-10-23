//---------------------------------------------------
//$JML,CAR,SAN,0,0,0,0,0,0;
//$JML,CAR,SAN,10,0,0,0,0,0;
//---------------------------------------------------
int CMD_FB = 0; //前后/俯仰：飞机、低头、抬头 Pitch
int CMD_YW = 0; //滚转：机头尾连线轴运动 Roll
int CMD_PW = 0; //油门
int CMD_RL = 0; //左右/偏航：机首机尾左右旋转 Yaw
//---------------------------------------------------
void CmdRun(){
  //-------------------------------------------------
  CMD_FB = getCmd[0].toInt();
  CMD_YW = getCmd[1].toInt();
  CMD_PW = getCmd[2].toInt();
  CMD_RL = getCmd[3].toInt();
  //-------------------------------------------------
  if(CMD_FB==0) {
    //RunStop();
    runsped = 0;
    runtype = 0;
  }
  else if(CMD_FB> 0) {
    //RunF( CMD_FB*2);
    runtype = 1;
    runsped = CMD_FB*2;
  }
  else if(CMD_FB< 0) {
    //RunB(-CMD_FB*2);
    runtype = -1;
    runsped = -CMD_FB*2;
  }
  //-------------------------------------------------
}

