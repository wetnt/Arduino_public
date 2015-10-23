// motor A
BBKMOTO mt;
public class BBKMOTO //类名称（可与文件名不同）
{
  int motoA1,motoA2,motoAS,motoB1,motoB2,motoBS;
  void BBKMOTO();
  void BBKMOTOS(int aa,int ac,int as,int ba,int bc,int bs){
    motoA1 = aa;
    motoA2 = ac;
    motoAS = as;
    motoB1 = ba;
    motoB2 = bc;
    motoBS = bs;
    pinMode(motoA1, OUTPUT);
    pinMode(motoA2, OUTPUT);
    pinMode(motoAS, OUTPUT);
    pinMode(motoB1, OUTPUT);
    pinMode(motoB2, OUTPUT);
    pinMode(motoBS, OUTPUT);
  };
  void MotoRun(int a,int s){
    if(s>255)s=255;
    analogWrite(motoBS, s);
    if (a == 0) {
      digitalWrite(motoB1, LOW);
      digitalWrite(motoB2, LOW);
    } 
    else if (a > 0) {
      digitalWrite(motoB1, HIGH);
      digitalWrite(motoB2, LOW);
    } 
    else if (a < 0) {
      digitalWrite(motoB1, LOW);
      digitalWrite(motoB2, HIGH);
    }
  };
  private: //此处定义私有函数和变量
};
