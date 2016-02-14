

void drawLine(int x1, int y1, int x2, int y2) {
  u8g.drawLine(x1, y1, x2, y2);
}
void D3D_Start() {
  //----------------------------------------
  moveObject(obj, 64, 32, 0);
  //----------------------------------------
  u8g.firstPage();
  do {
    renderObject(obj, qview);
  } while ( u8g.nextPage() );
  //----------------------------------------
}
CQuaternion q, qdelta = {0.999847695f, 0, 0.0174524f, 0}; //增量?
CEulerAngle r, g = {0.0349065844444444f, 0, 0};//YRP
void D3D_loop_run() {
  //----------------------------------------
  q = GetCQuaternion(g);
  r = GetEulerAngle(q.w,q.x,q.y,q.z); lg("Yaw, Pitch, Roll 1: "); lg(r.x); lg(", "); lg(r.y); lg(", "); lg(r.z);lg();
  //r = GetEulerAngle(qdelta.x,qdelta.z,q.y,q.w); lg("Yaw, Pitch, Roll 1: "); lg(r.x); lg(", "); lg(r.y); lg(", "); lg(r.z);
  qproduct(qdelta, obj.quat, qtemp);//融合旋转增量
  rotateObject(obj, qtemp);//旋转物体
  r = GetEulerAngle(qtemp.w,qtemp.x,qtemp.y,qtemp.z);
  //lg(" = "); lg(r.x); lg(", "); lg(r.y); lg(", "); lg(r.z); lg();
  //----------------------------------------
  u8g.firstPage();
  do {
    renderObject(obj, qview); //渲染物体
  } while ( u8g.nextPage() );
  //----------------------------------------
}
