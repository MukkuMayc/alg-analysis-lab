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

//using Edge = tuple<Vertex*, Vertex*, int64_t>;
using Edge = pair<Vertex*, Vertex*>;


struct Graph {
  vector<Vertex> V;
  vector<Edge> E;
  vector<int64_t> weight;
  explicit Graph(int vertNum): V(vertNum), E() {}
  Graph(): V(), E() {}
};

//inline void relax(Edge &edge) {
//  int64_t temp = get<0>(edge)->pathLen < INT64_MAX ? get<0>(edge)->pathLen + get<2>(edge) : INT64_MAX;
//  if (get<1>(edge)->pathLen > temp) {
//    get<1>(edge)->pathLen = temp;
//    get<1>(edge)->previous = get<0>(edge);
//  }
//}

inline void relax(Edge &edge, int64_t w) {
    int64_t temp = edge.first->pathLen < INT64_MAX ? edge.first->pathLen + w : INT64_MAX;
    if (edge.second->pathLen > temp) {
        edge.second->pathLen = temp;
        edge.second->previous = edge.first;
    }
}

inline bool BellmanFord(Graph &G, int s) {
  G.V[s].pathLen = 0;
  size_t limit = G.V.size() - 1;
  for (int i = 0; i < limit; ++i) {
//    for (auto &edge: G.E) {
    for (int j = 0; j < G.E.size(); ++j) {
      relax(G.E[j], G.weight[j]);
    }
  }
//  for (auto &edge: G.E) {
  for (int j = 0; j < G.E.size(); ++j) {
//    if (get<0>(edge)->pathLen < INT64_MAX and get<1>(edge)->pathLen > get<0>(edge)->pathLen + get<2>(edge)) {
    if (G.E[j].first->pathLen < INT64_MAX and G.E[j].second->pathLen > G.E[j].first->pathLen + G.weight[j]) {
      return false;
    }
  }
  return true;
}

#endif