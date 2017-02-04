String s = "www.bbkgps.com/t.php";
String wifurl = "www.bbkgps.com/v/jtwx/j.php?g=D4:EE:07:20:4D:50,D4:EE:07:20:4D:50,-45";
String urlHead = "www.bbkgps.com/v/jtwx/j.php?g=";
String myMac = "D4:EE:07:20:4D:50";
String wfMac = "D4:EE:07:20:4D:50";
String wfRss = "0";
void setup() {
  //------------------------------------------
  lgsetup(F("WIFI SCAN 1001"));
  wifi_setup();
  ss_init(F("SIM808"), 9600, true);
  gsm_init();
  //------------------------------------------
  printMacAddress();
  printWifiStatus();
  printWifiList();
  //------------------------------------------
  myMac = wifi_get_my_mac(); lg(myMac); lg();
  //------------------------------------------
}
void loop() {
  //lg("scan start"); lg();
  wfMac = wifi_get_ap_mac2(); lg(wfMac); lg();
  gsm_get_url(urlHead + myMac + "," + wfMac + "," + wfRss);;
  smartDelay(15000);
}
static void smartDelay(unsigned long ms) {
  unsigned long start = millis(); do {
    //------------------------------------------
    lgFeed(); ss_feed();
    //------------------------------------------
  } while (millis() - start < ms);
}
