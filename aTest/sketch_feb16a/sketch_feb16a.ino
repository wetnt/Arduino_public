
#define  lgs  Serial
static const long LGSBaud = 115200;

void setup() {
  lgs.begin(LGSBaud); delay(200);
  char* a = ConvertTo2String(22,8);
  lgs.println(a);
  a = ConvertTo2String(22,32);
  lgs.println(a);
}

void loop() {
  // put your main code here, to run repeatedly:

}

char *ConvertTo2String(long number, int n)
{
  char *output = NULL;
  output = (char*)malloc(33);    //include '\0'

  int i = 0;
  for (; i < n; i++)
  {
    output[i] = number & (1 << (n - 1) - i);
    output[i] = output[i] >> (n - 1) - i;
    output[i] = (output[i] == 0) ? '0' : '1';
  }
  output[i] = '\0';
  return output;
}
