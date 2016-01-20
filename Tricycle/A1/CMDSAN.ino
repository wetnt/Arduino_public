//---------------------------------------------------
//$JML,CAR,SAN,0,0,0,0,0,0;
//$JML,CAR,SAN,10,0,0,0,0,0;
//---------------------------------------------------
int CMD_YW = 0; //1滚转：机头尾连线轴运动 Roll
int CMD_FB = 0; //2前后/俯仰：飞机、低头、抬头 Pitch
int CMD_PW = 0; //3油门
int CMD_RL = 0; //4左右/偏航：机首机尾左右旋转 Yaw
//---------------------------------------------------
int updateTimeKey = 500;
//---------------------------------------------------
void CmdSet(){
  //-------------------------------------------------
  CMD_YW = getCmd[1].toInt();
  CMD_FB = getCmd[0].toInt();
  CMD_PW = getCmd[2].toInt();
  CMD_RL = getCmd[3].toInt();
  //-------------------------------------------------
}
void CmdDog(){
  //-------------------------------------------------
  if( millis()-updateTime > updateTimeKey ){
    CMD_FB = 0;
    CMD_YW = 0;
    CMD_PW = 0;
    CMD_RL = 0;
  };
}
void CmdLoop(float obstacleCm){
  //-------------------------------------------------
  if(obstacleCm<30 && CMD_FB>=0) {
    RunStop();
    return;
  }
  //-------------------------------------------------
  int typ = 0,spd = 0,rls = CMD_YW;
  CmdDog();
  //-------------------------------------------------
  if(CMD_FB==0) {
    typ = 0;
    spd = 0;
  }
  else if(CMD_FB> 0) {
    typ = 1;
    spd = CMD_FB;
  }
  else if(CMD_FB< 0) {
    typ = -1;
    spd = -CMD_FB;
  }
  //-------------------------------------------------
  MotoRunLoop(typ,spd,rls);
  //-------------------------------------------------
}



