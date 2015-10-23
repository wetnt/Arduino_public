
float Kp = 3;        // PID proportional control Gain
float Ki = 5;        // PID i control gain

float PID_updata(float targetValue, float currentValue)// compute PWM value
{
  //---------------------------------------------------------------
  float pidTerm = 0;// PID correction
  float error = 0;
  static float last_I = 0;
  //---------------------------------------------------------------
  error = abs(targetValue) - abs(currentValue);
  pidTerm =  Kp * error  + Kp * Ki * (error + last_I);
  last_I = error + last_I;
  //---------------------------------------------------------------
  return pidTerm;
  //---------------------------------------------------------------
}
