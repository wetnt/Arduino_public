typedef struct Vertex {
  int8_t location[3];
} MyVertex;
typedef struct Edge {
  int8_t connection[2];
} MyEdge;
typedef struct Object {
  int numv;
  int nume;
  MyVertex* v;
  MyEdge* e;
  float quat[4];
  float offset[3];
} MyObject;