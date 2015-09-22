//-------------------------------------------------------------------------
//char URL[400];
//char URLA[] = "AT+HTTPPARA=\"URL\",\"";
//char UseH[] = "www.bbkgps.com/v/g.php?n=boboking&p=123xjp&g=";
//char URLM[200];
//char URLD[] = "\"";
//-------------------------------------------------------------------------

//------------------------------------------
//log.print(gt.date.year()); log.print("-");
//log.print(gt.date.month()); log.print("-");
//log.print(gt.date.day()); log.print(" ");
//log.print(gt.time.hour()); log.print(":");
//log.print(gt.time.minute()); log.print(":");
//log.print(gt.time.second()); log.print("\t");
//------------------------------------------
//printDateTime(gt.date, gt.time); lg("    ");
//GpsTimeShow(g.dy,g.dm,g.dd,g.th,g.tm,g.ts);
//GpsTimeShow(g.tl);lg(" ");
//--------------------------------------------------------
//printFloat(g.w, true, 11, 8); lg(",");
//printFloat(g.j, true, 12, 8); lg(",");
//printFloat(g.h, true,  6, 0); lg(",");
//printFloat(g.v, true,  6, 2); lg("    ");
//--------------------------------------------------------
//lg("k="); lg(g.k); lg(",");
//lg("p="); lg(g.p); lg(",");
//lg("n="); printInt(g.n, true, 2); lg(",");
//lg("r="); printInt(g.r, true, 4); lg("    ");
//--------------------------------------------------------

//  void GprsHttpSet() {
//  //---------------------------------------------------------------
//  int dt = 200;
//  //---------------------------------------------------------------
//  lgln(F("GSM-Serial3.started.isRun!"));
//  if (GsmIsRun) {
//    //smartDelay(dt); GsmRunky = gprs.CmdSendOK(PNT, 2);  lg(GsmRunky); lgln(""); smartDelay(dt);
//    //smartDelay(dt); GsmRunky = gprs.CmdSendOK(SA1, 2);  lg(GsmRunky); lgln(""); smartDelay(dt);
//    //smartDelay(dt); GsmRunky = gprs.CmdSendOK(SA2, 2);  lg(GsmRunky); lgln(""); smartDelay(dt);
//  }
//  //---------------------------------------------------------------
//  //---------------------------------------------------------------
//}

//void SubmitHttpInt() {
//  //void CmdSend(String cmd, String backA, String backB, int TimeOutSecond)
//  //---------------------------------------------------------------
//  String bk = "";
//  bk = gprs.CmdSend(ATS, "OK", "", 2);
//  lg(bk);
//  GsmIsRun = bk == "OK";
//  //gsm.println(CSQ); smartDelay(1000);
//  //gsm.println(CRE); smartDelay(1000);
//  //gsm.println(CGA); smartDelay(1000);
//  //---------------------------------------
//  //gsm.println(SAP); smartDelay(1000);
//  //gsm.println(APN); smartDelay(5000);
//  //gsm.println(PNT); smartDelay(5000);
//  //---------------------------------------
//  //gsm.println(SA1); smartDelay(3000);
//  //gsm.println(SA2); smartDelay(3000);
//  //---------------------------------------------------------------
//}

//void SubmitHttpRequest(int delaysecond) {
//  //http://hi.baidu.com/robotkoko/item/f36367ebf921678ec10d7559
//  //---------------------------------------------------------------
//  sprintf(URL, "%.55s%f,%f,%f,%f,%f,%d,%ld000", UseH, g.w, g.j, g.h, g.v, g.x, g.r, g.n);
//  lgs.println(URL);
//  //String URL = "http://www.bbkgps.com/index.htm";
//  //---------------------------------------------------------------
//  gsm.println(URL); smartDelay(1000);
//  gsm.println(ACT); smartDelay(delaysecond * 1000);
//  gsm.println(REA); smartDelay(1000);
//  gsm.println("");
//  //---------------------------------------------------------------
//}

  //sprintf(URLM, "%s,%s,%s,%s,%s,%s,%s000", gs.w, gs.j, gs.h, gs.v, gs.x, gs.r, gs.tu);

//---------------------------------------
//  lgln( "GprsRun..." );
//  lg( "gprsRunTime..." );  lg( gprsRunTime ); lgln("");
//  lg( "gprsRunTimeKey..." );  lg( gprsRunTimeKey ); lgln("");
//  long x = gprsRunTime + gprsRunTimeKey;
//  lg( "gprsRun..." );  lg( x ); lgln("");
//  x = millis();
//  lg( "millis..." );  lg( x );  lgln("");
//---------------------------------------
