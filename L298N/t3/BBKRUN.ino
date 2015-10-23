//==========================================================
double Output= 0;
int count_right = 0;
int count_lefts = 0;
int pAIn = 1; 
int pBIn = 0; 
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
void RunF(int speed){
  //-----------------------------------
  Output = 1;
  int nx = count_right - count_lefts;
  //-----------------------------------
  if(nx==0){
    MotoRunA(1,speed);
    MotoRunB(1,speed);
  }
  else if(nx>0){
    MotoRunA(1,speed);
    MotoRunB(1,0);
  }
  else if(nx<0){
    MotoRunA(1,0);
    MotoRunB(1,speed);
  }
  //-----------------------------------
}
void RunB(int speed){
  //-----------------------------------
  Output = -1;
  int nx = count_right - count_lefts;
  //-----------------------------------
  if(nx==0){
    MotoRunA(-1,speed);
    MotoRunB(-1,speed);
  }
  else if(nx>0){
    MotoRunA(-1,0);
    MotoRunB(-1,speed);
  }
  else if(nx<0){
    MotoRunA(-1,speed);
    MotoRunB(-1,0);
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
void RunFL(int speed,int lr){
  //-----------------------------------
  if(lr>20)lr=20;
  //-----------------------------------
  Output = 1;
  int nx = count_right - count_lefts + lr;
  //-----------------------------------
  if(nx==0){
    MotoRunA(1,speed);
    MotoRunB(1,speed);
  }
  else if(nx>0){
    MotoRunA(1,speed);
    MotoRunB(1,0);
  }
  else if(nx<0){
    MotoRunA(1,0);
    MotoRunB(1,speed);
  }
  //-----------------------------------
}
//==========================================================



