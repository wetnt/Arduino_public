//作者：微风森林
//==========================================================================
MyObject  obj = {0, 0, mp, me, {1, 0, 0, 0}, {0, 0, 0}};
//==========================================================================
static CQuaternion qview = {0.99144486f, 0.13052619f, 0, 0};//观察点
static CQuaternion qtemp;
//==========================================================================
void D3D_load()   {
  obj.numv = sizeof(mp) / sizeof(MyVertex);
  obj.nume = sizeof(me) / sizeof(MyEdge);
  D3D_Start();
}
//==========================================================================
void moveObject(MyObject & mo, float x, float y, float z) { //offset位置
  mo.offset[0] = x; mo.offset[1] = y; mo.offset[2] = z;
}
void rotateObject(MyObject & mo, CQuaternion q) { //quat四元数姿态
  mo.quat = q;
}
void renderObject(MyObject & obj, CQuaternion view) { //渲染物体
  //----------------------------------------------------------------------------------
  MyVertex* mv = new MyVertex[obj.numv];
  //----------------------------------------------------------------------------------
  qproduct(view, obj.quat, qtemp);//融合观测视角
  //qnormalized(qtemp);//限定范围
  //----------------------------------------------------------------------------------
  for (int i = 0; i < obj.numv; i++) {
    iqRot(qtemp, obj.v[i].location, mv[i].location);
    mv[i].location[0] += obj.offset[0];
    mv[i].location[1] += obj.offset[1];
    mv[i].location[2] += obj.offset[2];
  }
  //----------------------------------------------------------------------------------
  for (int i = 0; i < obj.nume; i++) {
    int p1 = obj.e[i].connection[0];
    int p2 = obj.e[i].connection[1];
    //oled.drawline(mv[p1].location[0], mv[p1].location[1], mv[p2].location[0], mv[p2].location[1], WHITE);
    drawLine(mv[p1].location[0], mv[p1].location[1], mv[p2].location[0], mv[p2].location[1]);
  }
  //----------------------------------------------------------------------------------
  delete mv;
}
//==========================================================================
float iqRot(CQuaternion q, int v[], int result[]) {//融合qv
  float prod[4];
  prod[0] =  - q.x * v[0] - q.y * v[1] - q.z * v[2];
  prod[1] = q.w * v[0] + q.y * v[2] - q.z * v[1];
  prod[2] = q.w * v[1] - q.x * v[2] + q.z * v[0];
  prod[3] = q.w * v[2] + q.x * v[1] - q.y * v[0];
  result[0] = -prod[0] * q.x + prod[1] * q.w - prod[2] * q.z + prod[3] * q.y;
  result[1] = -prod[0] * q.y + prod[1] * q.z + prod[2] * q.w - prod[3] * q.x;
  result[2] = -prod[0] * q.z - prod[1] * q.y + prod[2] * q.x + prod[3] * q.w;
}
void qproduct(const CQuaternion p, const CQuaternion q, CQuaternion &qr) {//向量运算
  qr.x = p.x * q.x - p.y * q.y - p.z * q.z - p.w * q.w;
  qr.y = p.x * q.y + p.y * q.x + p.z * q.w - p.w * q.z;
  qr.z = p.x * q.z - p.y * q.w + p.z * q.x + p.w * q.y;
  qr.w = p.x * q.w + p.y * q.z - p.z * q.y + p.w * q.x;
}
//==========================================================================
//void qnormalized(float * q) {
//  float invnorm;
//  invnorm = fastinvsqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
//  if (invnorm < 100000000) {
//    q[0] *= invnorm; q[1] *= invnorm; q[2] *= invnorm; q[3] *= invnorm;
//  } else {
//    q[0] = 1; q[1] = 0; q[2] = 0; q[3] = 0;
//  }
//}
//float fastinvsqrt(float x) {
//  float halfx = 0.5f * x;
//  float y = x;
//  long i = *(long*)&y;
//  i = 0x5f3759df - (i >> 1);
//  y = *(float*)&i;
//  y = y * (1.5f - (halfx * y * y));
//  return y;
//}
//==========================================================================

