//==========================================================
int runtype = 0,runsped = 0;
void runLoop(){
  if(runtype == 0){
    RunStop();
  }else if(runtype == 1){
    RunF(runsped);
  }else if(runtype == -1){
    RunB(runsped);
  };
}
//==========================================================
double Output = 0;
int pAIn = 1,pBIn = 0; 
int count_right = 0,count_lefts = 0;
void Code_right(){  
  if(Output>=0){
    count_right += 1;
  }
  else{
    count_right -= 1;
  } 
}
void Code_lefts(){  
  if(Output>=0){
    count_lefts += 1;
  }
  else{
    count_lefts -= 1;
  } 
}
void Code_setIn(){  
  attachInterrupt(pAIn, Code_right, FALLING); 
  attachInterrupt(pBIn, Code_lefts, FALLING); 
}
void Code_Clear(){  
  count_right = 0;
  count_lefts = 0;
}
//==========================================================
void RunF(int spd){
  //-----------------------------------
  Output = 1;
  int nx = count_right - count_lefts;
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
void RunB(int spd){
  //-----------------------------------
  Output = -1;
  int nx = count_right - count_lefts;
  //-----------------------------------
  if(nx==0){
    MotoRunA(-1,spd);
    MotoRunB(-1,spd);
  }
  else if(nx>0){
    MotoRunA(-1,spd);
    MotoRunB(-1,0);
  }
  else if(nx<0){
    MotoRunA(-1,0);
    MotoRunB(-1,spd);
  }
  //-----------------------------------
}
void RunStop(){
  //-----------------------------------
  MotoRunA(0,0);
  MotoRunB(0,0);
  //-----------------------------------
}
//==========================================================
void RunFL(int spd,int lr){
  //-----------------------------------
  if(lr>20)lr=20;
  //-----------------------------------
  Output = 1;
  int nx = count_right - count_lefts + lr;
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
//==========================================================




