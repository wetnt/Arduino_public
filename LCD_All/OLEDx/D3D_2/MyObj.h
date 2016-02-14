typedef struct Vertex {
  int  location[3];
} MyVertex;
typedef struct Edge {
  int  connection[2];
} MyEdge;
typedef struct Object {
  int numv;
  int nume;
  MyVertex* v;
  MyEdge* e;
  float quat[4];
  float offset[3];
} MyObject;
