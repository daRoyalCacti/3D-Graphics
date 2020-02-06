/*#include "helper.h"

#ifdef better
std::vector<Vertex> to_vertex(std::vector<float> v, std::vector<float> u) {
  std::vector<Vertex> vertices;
  unsigned j = 0, k = 0;
  for (unsigned i = 0; i < v.size()/3; i++, j+=3, k+=2) {
    vertices[i] = {{v[j], v[j + 1], v[j + 2]}, {u[k], u[k + 1]}};
  }
  return vertices;
}
#endif*/
