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
void moveObject(MyObject &mo, float x, float y, float z) {//移动
  mo.offset[0] = x; mo.offset[1] = y; mo.offset[2] = z;
}
void rotateObject(MyObject &mo, CQuaternion q) {//旋转
  mo.quat = q;
  //for (int i = 0; i < 4; i++) mo.quat[i] = q[i];
}
void renderObject(MyObject &mo,CQuaternion view) {//渲染Object
  MyVertex* mv = new MyVertex[mo.numv];
  qproduct(view, mo.quat, qtemp);
  qnormalized(qtemp);
  for (int i = 0; i < mo.numv; i++) {
    iqRot(qtemp, mo.v[i].location, mv[i].location);
    mv[i].location[0] += mo.offset[0];
    mv[i].location[1] += mo.offset[1];
    mv[i].location[2] += mo.offset[2];
  }
  for (int i = 0; i < mo.nume; i++) {
    int p1 = mo.e[i].connection[0];
    int p2 = mo.e[i].connection[1];
    //oled.drawline(mv[p1].location[0], mv[p1].location[1], mv[p2].location[0], mv[p2].location[1], WHITE);
    drawLine(mv[p1].location[0], mv[p1].location[1], mv[p2].location[0], mv[p2].location[1]);
  }
  delete mv;
}
//========================================================
float iqRot(CQuaternion q, int v[], int result[]) {
  float prod[4];
  prod[0] =  - q.x * v[0] - q.y * v[1] - q.z * v[2];
  prod[1] = q.w * v[0] + q.y * v[2] - q.z * v[1];
  prod[2] = q.w * v[1] - q.x * v[2] + q.z * v[0];
  prod[3] = q.w * v[2] + q.x * v[1] - q.y * v[0];
  result[0] = -prod[0] * q.x + prod[1] * q.w - prod[2] * q.z + prod[3] * q.y;
  result[1] = -prod[0] * q.y + prod[1] * q.z + prod[2] * q.w - prod[3] * q.x;
  result[2] = -prod[0] * q.z - prod[1] * q.y + prod[2] * q.x + prod[3] * q.w;
}
void qproduct(const CQuaternion p, CQuaternion q, CQuaternion &qr) {
  qr.w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
  qr.x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
  qr.y = p.w * q.y - p.x * q.z + p.y * q.w + p.z * q.x;
  qr.z = p.w * q.z + p.x * q.y - p.y * q.x + p.z * q.w;
}
//========================================================
