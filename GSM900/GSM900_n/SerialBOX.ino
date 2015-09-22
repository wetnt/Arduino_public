void GpsInfoShow(){
  //---------------------------------------------------
  Serial.println("----");
  //-------------------------
  Serial.println(tDate);
  Serial.println(sLats);
  Serial.println(sLons);
  //-------------------------
  Serial.print(" h=");  Serial.print(sHigh);
  Serial.print(" s=");  Serial.print(sSped);
  Serial.print(" f=");  Serial.print(sFans);
  Serial.println();
  //-------------------------
  Serial.print(" y=");  Serial.print(cLock);
  Serial.print(" t=");  Serial.print(cType);
  Serial.print(" s=");  Serial.print(sGpsn);
  Serial.print(" r=");  Serial.print(sRads);
  Serial.print(" e=");  Serial.print(sSeal);
  Serial.println();
  //---------------------------------------------------
}
void GpsUrlStringShow(){
  //----------------------------------------------------------------
  //sprintf(URL,"%.55s%f,%f,%f,%f,%f,%d,%ld000",UseH,gi.WW,gi.JJ,gi.HH,gi.VV,gi.FX,gi.SR,utctime);
  sprintf(URL,"%.55s%.9s,%.10s,%s,%s,%s,%ld000",UseH,sLats,sLons,sHigh,sSped,sFans,utctime);
  Serial.println(URL);
  //----------------------------------------------------------------
}
