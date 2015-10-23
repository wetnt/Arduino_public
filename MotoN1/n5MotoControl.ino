int PWM_val_r = 0;
int PWM_val_l = 0;
float v_req_r = 0;
float v_req_l = 0;
const int LOOPTIME = 50;  //the loop time(ms) of PID control

const int NUM_C_l = 16;
const int NUM_C_r = 16;   //the number of counter of a roll.
//IF select CHANGE in attachInterrupt(0, rencoder, CHANGE) ,the  NUM_C should be multiple by 2
//Other selection in attachInterrupt(0, rencoder, FALLING), the  NUM_C is equal to the number of counter of a roll

void forward()
{
  v_req_r = 1.56;
  v_req_l = 1.56;
  //motor_r(PWM_val_r);
  motor_l(PWM_val_l);
  //PWM_val_r = control_loop_r(LOOPTIME, v_req_r, PWM_val_r);
  PWM_val_l = control_loop_l(LOOPTIME, v_req_l, PWM_val_l);
}

int control_loop_l(int looptime , float speed_req_l, int PWM_val_l)
{
  //---------------------------------------------------------------
  long lastMilli_l = millis();
  long count_fomer_l;
  float speed_act_l;
  //---------------------------------------------------------------
  count_fomer_l = count_l;
  //---------------------------------------------------------------
  interrupts();
  while ((millis() - lastMilli_l) <= looptime)
  {
    ;   // enter tmed loop
  }
  noInterrupts();
  //---------------------------------------------------------------
  speed_act_l = float(count_l - count_fomer_l) * 1000 / float(looptime * NUM_C_l);
  //---------------------------------------------------------------
  Serial.print("Left Speed is "); Serial.println(speed_act_l);
  PWM_val_l = PID_updata(speed_req_l, speed_act_l);  // compute PWM
  //---------------------------------------------------------------
  return constrain(PWM_val_l, 0, 255);
  //---------------------------------------------------------------
}
