#ifndef __MY_BELLMAN_FORD__
#define __MY_BELLMAN_FORD__

#include <cstdint>
#include <vector>

using namespace std;

struct Vertex {
  int64_t pathLen;
  Vertex* previous;
  vector<pair<Vertex*, int64_t>> edges;
  Vertex(): pathLen(INT64_MAX), previous(nullptr) {}
};

inline void relax(Vertex &u, Vertex &v, int64_t w) {
  int temp = u.pathLen + w;
  if (v.pathLen > temp) {
    v.pathLen = temp;
  }
}

bool BellmanFord(vector<Vertex> &vertices, int s) {
  vertices[s].pathLen = 0;
  for (int i = 0; i < vertices.size() - 1; ++i) {
    for (Vertex &u: vertices) {
      for (auto &edge: u.edges) {
        relax(u, *edge.first, edge.second);
      }
    }
  }
  for (Vertex &u: vertices) {
    for (auto &edge: u.edges) {
      if ((*edge.first).pathLen > u.pathLen + edge.second) {
        return false;
      }
    }
  }
  return true;
}

#endif