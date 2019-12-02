#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

#include "bellman-ford.cpp"

using namespace std;

TEST(BellmanFord, CreateGraph) {
  vector<Vertex> G(1);
  ASSERT_EQ(G[0].pathLen, INT64_MAX);
  ASSERT_EQ(G[0].previous, nullptr);
  ASSERT_EQ(G[0].edges.size(), 0);
}

TEST(BellmanFord, MoveGraph) {
  vector<Vertex> G(1);
  G[0].pathLen = 10;
  vector<Vertex> V;
  V = move(G);
  ASSERT_EQ(V[0].pathLen, 10);
}

TEST(BellmanFord, PosEdgesNoCycles) {
  vector<Vertex> G(5);
  G[0].edges.emplace_back(make_pair(&G[1], 4));
  G[0].edges.emplace_back(make_pair(&G[2], 1));
  G[2].edges.emplace_back(make_pair(&G[1], 5));
  G[2].edges.emplace_back(make_pair(&G[3], 1));
  G[3].edges.emplace_back(make_pair(&G[1], 1));
  G[3].edges.emplace_back(make_pair(&G[4], 8));
  bool thereAreNotNegativeCycles = BellmanFord(G, 0);

  cout << G[0].pathLen << endl;
  cout << G[1].pathLen << endl;
  cout << G[2].pathLen << endl;
  cout << G[3].pathLen << endl;
  cout << G[4].pathLen << endl;

  ASSERT_EQ(thereAreNotNegativeCycles, true);
  ASSERT_EQ(G[0].pathLen, 0);
  ASSERT_EQ(G[1].pathLen, 3);
  ASSERT_EQ(G[2].pathLen, 1);
  ASSERT_EQ(G[3].pathLen, 2);
  ASSERT_EQ(G[4].pathLen, 10);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}