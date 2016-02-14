//================================================================
CEulerAngle GetEulerAngle(CQuaternion q) {
  qnormalized(q); return GetEulerAngle(q.w, q.x, q.y, q.z);
}
//================================================================
// 由四元数返回欧拉角
CEulerAngle GetEulerAngle(float w, float x, float y, float z) {
  //----------------------------------------------------------------------------------
  CEulerAngle ret;
  //----------------------------------------------------------------------------------
  float test = y * z + x * w;
  if (test > 0.4999f) {
    ret.z = GetDeg(2.0f * atan2(y, w)); ret.x = 90; ret.y = 0.0f;
    return ret;
  }
  if (test < -0.4999f) {
    ret.z = GetDeg(2.0f * atan2(y, w)); ret.x = -90; ret.y = 0.0f;
    return ret;
  }
  //----------------------------------------------------------------------------------
  //ret.x = asin(2.0f * x * y - 2.0f *w * z); // pitch//
  ret.x = 2.0f * asin(2.0f * test); float sqx = x * x, sqy = y * y, sqz = z * z;
  ret.y = atan2(2.0f * y * w - 2.0f * z * x, 1.0f - 2.0f * sqy - 2.0f * sqx);
  ret.z = atan2(2.0f * z * w - 2.0f * y * x, 1.0f - 2.0f * sqz - 2.0f * sqx);
  ret.x = GetDeg(ret.x); ret.y = GetDeg(ret.y); ret.z = GetDeg(ret.z);
  //----------------------------------------------------------------------------------
  return ret;
  //----------------------------------------------------------------------------------
};
float GetDeg(float x) {
  return x * 180.0f / PI;
}
//========================================================
// 由欧拉角创建四元数
CQuaternion GetCQuaternion(CEulerAngle angle) {
  CQuaternion q;
  float cx = cos(angle.x / 2);
  float sx = sin(angle.x / 2);
  float cy = cos(angle.y / 2);
  float sy = sin(angle.y / 2);
  float cz = cos(angle.z / 2);
  float sz = sin(angle.z / 2);
  q.w = cx * cy * cz + sx * sy * sz;
  q.x = sx * cy * cz - cx * sy * sz;
  q.y = cx * sy * cz + sx * cy * sz;
  q.z = cx * cy * sz - sx * sy * cz;
  qnormalized(q);
  return q;
};
//========================================================
void qnormalized(CQuaternion &q) {//四元数标准化
  float invnorm = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
  invnorm = fastInvSqrt(invnorm);
  if (invnorm < 100000000) {
    q.w *= invnorm; q.x *= invnorm; q.y *= invnorm; q.z *= invnorm;
  } else {
    q.w = 1; q.x = 0; q.y = 0; q.z = 0;
  }
}
float fastInvSqrt(float x) {//快速倒置开方
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
  return y;
}
//========================================================
