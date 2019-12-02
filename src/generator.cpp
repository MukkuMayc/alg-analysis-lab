#ifndef __MY_GENERATOR__
#define __MY_GENERATOR__

#include <random>
#include "bellman-ford.cpp"

using namespace std;

vector<Vertex> generateGraph(int vertNum, int edgeNum) {
  default_random_engine generator;
  uniform_int_distribution<int> verticesDistribution(0, vertNum - 1);
  uniform_int_distribution<int> pathLenDistribution(-10, 10);
  vector<Vertex> G(vertNum);
  for (int i = 0; i < edgeNum; ++i) {
    int u = verticesDistribution(generator);
    int v = verticesDistribution(generator);
    int w = pathLenDistribution(generator);
    G[u].edges.emplace_back(make_pair(&G[v], w));
  }
  return G;
}

#endif