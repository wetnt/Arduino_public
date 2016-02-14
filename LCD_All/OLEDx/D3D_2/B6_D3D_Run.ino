

void drawLine(int x1, int y1, int x2, int y2) {
  u8g.drawLine(x1, y1, x2, y2);
}
void D3D_Start(){
    moveObject(obj, 64, 32, 0);
   // rotateObject(obj, 3.0);
  //renderObject(obj);
      //----------------------------------------
  u8g.firstPage();
  do {
    renderObject(obj);
  } while ( u8g.nextPage() );
  //----------------------------------------
}
void D3D_loop_run() {
  //----------------------------------------
  qproduct(qdelta, obj.quat, qtemp);
  rotateObject(obj, qtemp);
  //----------------------------------------
  u8g.firstPage();
  do {
    renderObject(obj);
  } while ( u8g.nextPage() );
  //----------------------------------------
}
