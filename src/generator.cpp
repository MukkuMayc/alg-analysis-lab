#ifndef __MY_GENERATOR__
#define __MY_GENERATOR__

#include <random>
#include <chrono>
#include "bellman-ford.cpp"

using namespace std;

Graph generateGraph(const int vertNum, const int edgeNum) {
  auto now = chrono::system_clock::now();
  default_random_engine generator(now.time_since_epoch().count());
  uniform_int_distribution<int> verticesDistribution(0, vertNum - 1);
  uniform_int_distribution<int> pathLenDistribution(-10, 10);
  Graph G(vertNum);
  G.E.reserve(edgeNum);
  for (int i = 0; i < edgeNum; ++i) {
    int u = verticesDistribution(generator);
    int v = verticesDistribution(generator);
    int w = pathLenDistribution(generator);
    G.E.emplace_back(make_pair(&G.V[u], &G.V[v]));
    G.weight.emplace_back(w);
  }
  return G;
}

#endif