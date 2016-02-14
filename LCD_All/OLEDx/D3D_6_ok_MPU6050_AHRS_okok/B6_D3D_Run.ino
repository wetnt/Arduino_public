//================================================================
void D3D_Start() {
  //----------------------------------------
  moveObject(obj, 64, 32, 0);
  AHRS_Show(obj, F("obj.A."));
  //----------------------------------------
  u8g.firstPage();
  do {
    renderObject(obj, qview);
  } while ( u8g.nextPage() );
  //----------------------------------------
}
CEulerAngle g = {0.0349065844444444f, 0.0f, 0.0f}; //Pitch/Yaw/Roll
CQuaternion q;//qdelta = {0.999847695f, 0, 0.0174524f, 0}; //增量?
void D3D_loop_run() {
  //----------------------------------------
  g.z=imu.rollRad;           //横滚deg
  g.x=-imu.pitchRad;          //俯仰
  g.y=imu.yawRad;            //航向
  qtemp = GetCQuaternion(g);
  //----------------------------------------
  //qproduct(q, obj.quat, qtemp);//融合旋转增量
  rotateObject(obj, qtemp);//旋转物体
  AHRS_Show(obj, "obj.");
  //----------------------------------------
  u8g.firstPage();
  do {
    renderObject(obj, qview); //渲染物体
  } while ( u8g.nextPage() );
  //----------------------------------------
}
//================================================================
CEulerAngle r;
void AHRS_Show(MyObject mo, String s) {
  //----------------------------------------
  r = GetEulerAngle(mo.quat);
  lg(s); lg("Pitch/Yaw/Roll = "); lg(r.x); lg(", "); lg(r.y); lg(", "); lg(r.z); lg();
  //----------------------------------------
}
void AHRS_Show(CQuaternion q, String s) {
  //----------------------------------------
  r = GetEulerAngle(q);
  lg(s); lg("Pitch/Yaw/Roll = "); lg(r.x); lg(", "); lg(r.y); lg(", "); lg(r.z); lg();
  //----------------------------------------
  //r = GetEulerAngle(qdelta.w,qdelta.x,qdelta.y,qdelta.z); lg("Yaw, Pitch, Roll 1: "); lg(r.x); lg(", "); lg(r.y); lg(", "); lg(r.z);
  //r = GetEulerAngle(qtemp.w,qtemp.x,qtemp.y,qtemp.z);lg(" = "); lg(r.x); lg(", "); lg(r.y); lg(", "); lg(r.z); lg();
  //----------------------------------------
}
//================================================================

