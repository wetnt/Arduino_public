//--------------------------------------------------
int value = 0;
const char* host = "www.lewei50.com";
const int   port = 80;
const int   timeOut = 30 * 1000;
//--------------------------------------------------
float WDLD = random(10, 30);
void WIFI_Lewei_Report() {
  WDLD = random(10, 30);
  GetLeweiPostString(Lewei_Keys, "02", Lewei_ValueJson(WDLD)); //lgln(Lewei_Post);
  if (WIFI_GET_POST(host, port, timeOut, Lewei_Post, false)) {
    String x = GetStringAB(NET_GET_POST_BACK, "Date:", "GMT"); WIFI_TIME_EXP(x);
    x = GetStringAB(NET_GET_POST_BACK, "{", "}"); lgln(x);
  } else {
  }
}
