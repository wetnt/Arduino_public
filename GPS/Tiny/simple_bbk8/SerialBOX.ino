void GpsInfoShow(){
  //---------------------------------------------------
  Serial.println("----");
  //-------------------------
  Serial.println(gs.tDate);
  Serial.println(gs.sLats);
  Serial.println(gs.sLons);
  //-------------------------
  Serial.print(" h=");  Serial.print(gs.sHigh);
  Serial.print(" s=");  Serial.print(gs.sSped);
  Serial.print(" f=");  Serial.print(gs.sFans);
  Serial.println();
  //-------------------------
  Serial.print(" y=");  Serial.print(gs.cLock);
  Serial.print(" t=");  Serial.print(gs.cType);
  Serial.print(" s=");  Serial.print(gs.sGpsn);
  Serial.print(" r=");  Serial.print(gs.sRads);
  Serial.print(" e=");  Serial.print(gs.sSeal);
  Serial.println();
  //---------------------------------------------------
}
void GpsUrlStringShow(){
  //----------------------------------------------------------------
  //sprintf(URL,"%.55s%f,%f,%f,%f,%f,%d,%ld000",UseH,gi.WW,gi.JJ,gi.HH,gi.VV,gi.FX,gi.SR,utctime);
  sprintf(URL,"%.55s%.9s,%.10s,%s,%s,%s,%ld000",UseH,gs.sLats,gs.sLons,gs.sHigh,gs.sSped,gs.sFans,utctime);
  Serial.println(URL);
  //----------------------------------------------------------------
}
