typedef struct charCheckSave {
  int len = 0;
  int inx = 0;
  String str = "";
  void init(String s) {
    str = s; inx = 0;
    len = s.length();
    lg(len); lg();
  }
  boolean check(char c) {
    lg("="); lg(c); lg("="); lg(inx); lg();
    if (len == 0) return false;
    if (inx == len - 1) {
      inx = 0; return true;
    }
    if (str[inx] == c) inx++; else inx = 0;
    return false;
  }
} charCheckSave;

charCheckSave c1;

static char Lewei_Date[] = "Date:";
static char Lewei_Gmts[] = "GMT";



void setup() {
  lgsetup("charCheckSave...");
  c1.init(Lewei_Date);
}

void loop() {
  lgFeed();

}

