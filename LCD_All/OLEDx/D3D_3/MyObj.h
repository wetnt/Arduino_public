typedef struct Vertex {
  int  location[3];
} MyVertex;
typedef struct Edge {
  int  connection[2];
} MyEdge;
typedef struct CQuaternion {
  float x;
  float y;
  float z;
  float w;
} CQuaternion;
typedef struct Object {
  int numv;
  int nume;
  MyVertex* v;//顶点
  MyEdge* e;//边缘（顶点连接线）
  CQuaternion quat;//Quaternions四元数姿态
  float offset[3];//位置(偏移)
} MyObject;
typedef struct CEulerAngle {
  float x;//Yaw
  float y;//Pitch?
  float z;//Roll?
} CEulerAngle;
