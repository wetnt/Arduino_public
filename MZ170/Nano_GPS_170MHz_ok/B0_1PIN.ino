//===================================================================
int Pinx[6] = {A0, A1, A2, A3, A6, A7};
void Pin_setup(){
  //-------------------------------------
  for (int i = 0; i < 6; i++) pinMode(Pinx[i], INPUT);
  //-------------------------------------  
}

