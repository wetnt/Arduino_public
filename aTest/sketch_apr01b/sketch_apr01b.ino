float average(int ParaNum, ...) {
  va_list va_Average;
  int count;
  int sum;
  va_start(va_Average, ParaNum);
  for (count = 1; count < ParaNum; count++) {
    sum += va_arg(va_Average, int);
    Serial.println(sum);
  }
  va_end(va_Average);
  return (float)(sum / ParaNum);
}

String Lewei_Build(int n, ...) {
  va_list va_b;
  String sum;
  va_start(va_b, n);
  for (int i = 1; i < n; i++) {
    Serial.println(va_arg(va_b, int));
  }
  va_end(va_b);
  return sum;
}

FILE *logfile;
int WriteLog(const char * format, ...){
  va_list arg_ptr;
  va_start(arg_ptr, format);
  int nWrittenBytes = vfprintf(logfile, format, arg_ptr);  
  va_end(arg_ptr);
  return nWrittenBytes;
}




void setup() {
  Serial.begin(115200);
  Lewei_Build(4, "a", "b", "c");

int x = WriteLog("%04d-%02d-%02d %02d:%02d:%02d  %s/%04d logged out.",
           2016, 3,8, 1,1,1,222);

            Serial.println(x); 

           
}

void loop() {
}
