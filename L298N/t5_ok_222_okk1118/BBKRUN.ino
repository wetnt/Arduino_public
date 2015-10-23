//==========================================================
int typelast = 0;
void LastTypeSet(int type){
  if(typelast!=type){
    Code_Clear();
  }
  typelast = type;  
}
void MotoRunLoop(int runtype,int runsped,int runrorl){
  //-----------------------------------
  LastTypeSet( runtype );
  //-----------------------------------
  runrorl = runrorl / 5;
  runsped = runsped * 3;
  //-----------------------------------
  if(runtype == 0){
    RunStop();    
  }
  else if(runtype == 1){
    RunF(runsped,runrorl);
  }
  else if(runtype == -1){
    RunB(runsped,runrorl);
  }
  //-----------------------------------
}
//==========================================================
void RunF(int spd,int rol){
  //-----------------------------------
  Output = 1;
  int nx = count_right - count_lefts - rol;
  //-----------------------------------
  if(nx==0){
    MotoRunA(1,spd);
    MotoRunB(1,spd);
  }
  else if(nx>0){
    MotoRunA(1,spd);
    MotoRunB(1,0);
  }
  else if(nx<0){
    MotoRunA(1,0);
    MotoRunB(1,spd);
  }
  //-----------------------------------
}
void RunB(int spd,int rol){
  //-----------------------------------
  Output = -1;
  int nx = count_right - count_lefts - rol;
  //-----------------------------------
  if(nx==0){
    MotoRunA(-1,spd);
    MotoRunB(-1,spd);
  }
  else if(nx>0){
    MotoRunA(-1,0);
    MotoRunB(-1,spd);
  }
  else if(nx<0){
    MotoRunA(-1,spd);
    MotoRunB(-1,0);
  }
  //-----------------------------------
}
void RunStop(){
  //-----------------------------------
  MotoRunA(0,0);
  MotoRunB(0,0);
  Code_Clear();
  //-----------------------------------
}
//==========================================================
//==========================================================





