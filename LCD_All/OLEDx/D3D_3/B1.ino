// 由四元数返回欧拉角
CEulerAngle GetEulerAngle(float x, float y, float z, float w) {
  //----------------------------------------------------------------------------------
  CEulerAngle ret;
  //----------------------------------------------------------------------------------
  float test = y * z + x * w;
  if (test > 0.4999f) {
    ret.z = GetDeg(2.0f * atan2(y, w)); ret.y = 90; ret.x = 0.0f;
    return ret;
  }
  if (test < -0.4999f) {
    ret.z = GetDeg(2.0f * atan2(y, w)); ret.y = -90; ret.x = 0.0f;
    return ret;
  }
  //----------------------------------------------------------------------------------
  float sqx = x * x, sqy = y * y, sqz = z * z;
  ret.y = asin(2.0f * test);
  ret.x = atan2(2.0f * y * w - 2.0f * z * x, 1.0f - 2.0f * sqy - 2.0f * sqx);
  ret.z = atan2(2.0f * z * w - 2.0f * y * x, 1.0f - 2.0f * sqz - 2.0f * sqx);
  ret.z = GetDeg(ret.z); ret.y = GetDeg(ret.y); ret.x = GetDeg(ret.x);
  //----------------------------------------------------------------------------------
  //lg("Yaw, Pitch, Roll 1: "); Serial.print(ret.x, 2); Serial.print(", "); Serial.print(ret.y, 2); Serial.print(", "); Serial.println(ret.z, 2);
  return ret;
  //----------------------------------------------------------------------------------
};
float GetDeg(float x) {
  return x * 180.0f / PI;
}
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
  return q;
};
