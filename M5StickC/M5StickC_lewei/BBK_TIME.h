//======================================
typedef struct {
  //--------------------------------------------------
  int tz = 8;
  int th, tm, ts;
  int dd, dm, dy;
  char time_str[10];
  String time_sting;
  //--------------------------------------------------
  void time_to_string() {
    snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", th, tm, ts);
    String tms = String(tm); if (tms.length() == 1) tms = "0" + tms;
    String tss = String(ts); if (tss.length() == 1) tss = "0" + tss;
    time_sting = String(th) + ":" + tms + ":" + tss;
  }
  //--------------------------------------------------
  void setTime(int h, int m, int s, int z) {
    tz = z; th = h + z; tm = m; ts = s;
    if (th >= 24) {
      th = th - 24;
      dd++;
    }
    time_to_string();
  }
  void setTime(int h, int m, int s, int d, int n, int y, int z) {
    tz = z; th = h + z; tm = m; ts = s; dd = d; dm = n; dy = y;
    if (th >= 24) {
      th = th - 24;
      dd++;
    }
    time_to_string();
  }
  //--------------------------------------------------
  void time_by_string(String x, int tzone) {
    String ths = x.substring(0, 2);
    String tms = x.substring(3, 5);
    String tss = x.substring(6, 8);
    setTime(ths.toInt(), tms.toInt(), tss.toInt(), tzone);
  }
  //--------------------------------------------------
  void addTimeSecond() {
    ts++;
    if (ts >= 60) {
      ts = 0; tm++;
    }
    if (tm >= 60) {
      tm = 0; th++;
    }
    if (th >= 24) {
      th = 0; dd++;
    }
    time_to_string();
  }
  //--------------------------------------------------
} BBK_Time;
BBK_Time dt;
