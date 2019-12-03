#ifndef __MY_BELLMAN_FORD__
#define __MY_BELLMAN_FORD__

#include <cstdint>
#include <vector>
#include <tuple>

using namespace std;

struct Vertex {
  int64_t pathLen;
  Vertex* previous;
  Vertex(): pathLen(INT64_MAX), previous(nullptr) {}
};

using Edge = tuple<Vertex*, Vertex*, int64_t>;

struct Graph {
  vector<Vertex> V;
  vector<Edge> E;
  explicit Graph(int vertNum): V(vertNum), E() {}
  Graph(): V(), E() {}
};

inline void relax(Edge &edge) {
  int64_t temp = get<0>(edge)->pathLen < INT64_MAX ? get<0>(edge)->pathLen + get<2>(edge) : INT64_MAX;
  if (get<1>(edge)->pathLen > temp) {
    get<1>(edge)->pathLen = temp;
    get<1>(edge)->previous = get<0>(edge);
  }
}

inline bool BellmanFord(Graph &G, int s) {
  G.V[s].pathLen = 0;
  int limit = G.V.size() - 1;
  for (int i = 0; i < limit; ++i) {
    for (auto &edge: G.E) {
      relax(edge);
    }
  }
  for (auto &edge: G.E) {
    if (get<0>(edge)->pathLen < INT64_MAX and get<1>(edge)->pathLen > get<0>(edge)->pathLen + get<2>(edge)) {
      return false;
    }
  }
  return true;
}

#endif