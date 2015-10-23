//==========================================================
double Output = 0;
int pAIn = 3,pBIn = 2; 
int count_right = 0,count_lefts = 0;
//==========================================================
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
