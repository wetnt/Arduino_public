void GpsUrlStringShow(){
  //----------------------------------------------------------------  
  sprintf(
    URL,
  "%.55s%.9s,%.10s,%s,%s,%s,%ld000",
    UseH,gs.sLats,gs.sLons,gs.sHigh,gs.sSped,gs.sFans,utctime
  );
  Serial.println(URL);
  //----------------------------------------------------------------
}
