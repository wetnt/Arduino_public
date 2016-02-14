//作者：微风森林
//========================================================
static MyVertex mp[] = {
  { -16, -16, -16},  {16, -16, -16},//
  {16, 16, -16},  { -16, 16, -16},  //
  { -16, -16, 16},  {16, -16, 16},  //
  {16, 16, 16},  { -16, 16, 16}     //
};
static MyEdge me[] = {
  {0, 1}, {1, 2}, {2, 3}, {3, 0}, //
  {4, 5}, {5, 6}, {6, 7}, {7, 4}, //
  {0, 4}, {1, 5}, {2, 6}, {3, 7}  //
};
//新增纸飞机代码如下
//static MyVertex mp[] = {{ -20, 0, -20}, {0, 0, 20}, {20, 0, -20}, {0, 0, -20}, {0, 10, -20}};
//static MyEdge me[] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 3}, {3, 0}};
MyObject  obj = {0, 0, mp, me, {1, 0, 0, 0}, {0, 0, 0}};
//========================================================
static float qdelta[4] = {0.999847695f, 0, 0.0174524f, 0};
static float qview[4]  = {0.99144486f, 0.13052619f, 0, 0};
static float qtemp[4];
//========================================================
void D3D_setup()   {
  obj.numv = sizeof(mp) / sizeof(MyVertex);
  obj.nume = sizeof(me) / sizeof(MyEdge);
  //moveObject(obj, 64, 32, 0);
  //renderObject(obj);
  D3D_Start();
}
void D3D_loop() {
  qproduct(qdelta, obj.quat, qtemp);
  rotateObject(obj, qtemp);
  renderObject(obj);
}
//========================================================
void moveObject(MyObject mo, float x, float y, float z) { //移动
  mo.offset[0] = x; mo.offset[1] = y; mo.offset[2] = z;
}
void rotateObject(MyObject &mo, float* q) {//旋转
  //for (int i = 0; i < 4; i++) mo.quat[i] = q[i];
  mo.quat[0] = q[0];
  mo.quat[1] = q[1];
  mo.quat[2] = q[2];
  mo.quat[3] = q[3];
}
void renderObject(MyObject &mo) {//渲染Object
  MyVertex* mv = new MyVertex[mo.numv];
  qproduct(qview, mo.quat, qtemp);
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
float iqRot(float q[], int v[], int result[]) {
  float prod[4];
  prod[0] =  - q[1] * v[0] - q[2] * v[1] - q[3] * v[2];
  prod[1] = q[0] * v[0] + q[2] * v[2] - q[3] * v[1];
  prod[2] = q[0] * v[1] - q[1] * v[2] + q[3] * v[0];
  prod[3] = q[0] * v[2] + q[1] * v[1] - q[2] * v[0];
  result[0] = -prod[0] * q[1] + prod[1] * q[0] - prod[2] * q[3] + prod[3] * q[2];
  result[1] = -prod[0] * q[2] + prod[1] * q[3] + prod[2] * q[0] - prod[3] * q[1];
  result[2] = -prod[0] * q[3] - prod[1] * q[2] + prod[2] * q[1] + prod[3] * q[0];
}
void qproduct(const float* p, const float* q, float* qr) {
  qr[0] = p[0] * q[0] - p[1] * q[1] - p[2] * q[2] - p[3] * q[3];
  qr[1] = p[0] * q[1] + p[1] * q[0] + p[2] * q[3] - p[3] * q[2];
  qr[2] = p[0] * q[2] - p[1] * q[3] + p[2] * q[0] + p[3] * q[1];
  qr[3] = p[0] * q[3] + p[1] * q[2] - p[2] * q[1] + p[3] * q[0];
}
void qnormalized(float* q) {//标准化
  float invnorm;
  invnorm = fastinvsqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
  if (invnorm < 100000000) {
    q[0] *= invnorm; q[1] *= invnorm; q[2] *= invnorm; q[3] *= invnorm;
  } else {
    q[0] = 1; q[1] = 0; q[2] = 0; q[3] = 0;
  }
}
float fastinvsqrt(float x) {
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
  return y;
}
//========================================================

