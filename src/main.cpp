#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <cassert>
#include "bellman-ford.cpp"
#include "generator.cpp"

using namespace std;

int main() {
  ofstream output("output.csv");
  output << setprecision(3);
  int vertBegin = 1;
  int edgeBegin = 1;
  int vertLimit = (1 << 13) + 1;
  int edgeLimit = (1 << 16) + 1;
  for (int edgeNum = edgeBegin; edgeNum < edgeLimit; edgeNum *= 2) {
    output << ',' << edgeNum;
  }
  output << endl;

  for (int vertNum = vertBegin; vertNum < vertLimit; vertNum *= 2) {
    output << vertNum;
    for (int edgeNum = edgeBegin; edgeNum < edgeLimit; edgeNum *= 2) {
      auto G = generateGraph(vertNum, edgeNum);

      assert(G.V.size() == vertNum);
      assert(G.E.size() == edgeNum);

      auto start = chrono::high_resolution_clock::now();
      BellmanFord(G, 0);
      auto end = chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>
                          (end - start).count() / 1e9;

      output << ',' << duration;

      size_t notReachNum = 0;
      for (auto &v: G.V) {
        notReachNum += (v.pathLen == INT64_MAX);
      }
      cout << vertNum << ".." << edgeNum << ".." << notReachNum << endl;
    }
    output << endl;
  }

  return 0;
}
