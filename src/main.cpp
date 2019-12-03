#include <fstream>
#include <chrono>
#include <iomanip>
#include "bellman-ford.cpp"
#include "generator.cpp"

int main() {
  ofstream output("output.csv");
  output << setprecision(3);
  int vertLimit = 1e4 + 1;
  int edgeLimit = 1e5 + 1;
  for (int edgeNum = 1; edgeNum < edgeLimit; edgeNum *= 2) {
    output << ',' << edgeNum;
  }
  output << endl;

  for (int vertNum = 1; vertNum < vertLimit; vertNum *= 2) {
    output << vertNum;
    for (int edgeNum = 1; edgeNum < edgeLimit; edgeNum *= 2) {
      auto G = generateGraph(vertNum, edgeNum);
      auto start = chrono::high_resolution_clock::now();
      BellmanFord(G, 0);
      auto end = chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>
                          (end - start).count() / 1e9;
      output << ',' << duration;
    }
    output << endl;
  }

  return 0;
}
