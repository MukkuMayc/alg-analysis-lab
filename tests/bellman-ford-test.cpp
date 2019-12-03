#include "gtest/gtest.h"
#include <vector>
#include <cstdint>
#include <chrono>

#include "bellman-ford.cpp"
#include "generator.cpp"

using namespace std;

TEST(BellmanFord, CreateGraph) {
  Graph G(1);
  ASSERT_EQ(G.V[0].pathLen, INT64_MAX);
  ASSERT_EQ(G.V[0].previous, nullptr);
  ASSERT_EQ(G.E.size(), 0);
}

TEST(BellmanFord, MoveGraph) {
  Graph G(1);
  G.V[0].pathLen = 10;
  Graph V;
  V = move(G);
  ASSERT_EQ(V.V[0].pathLen, 10);
}

TEST(BellmanFord, PosEdgesNoCycles) {
  Graph G(5);
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[1], 4));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[2], 1));
  G.E.emplace_back(make_tuple(&G.V[2], &G.V[1], 5));
  G.E.emplace_back(make_tuple(&G.V[2], &G.V[3], 1));
  G.E.emplace_back(make_tuple(&G.V[3], &G.V[1], 1));
  G.E.emplace_back(make_tuple(&G.V[3], &G.V[4], 8));
  bool thereAreNotNegativeCycles = BellmanFord(G, 0);

  ASSERT_EQ(thereAreNotNegativeCycles, true);
  ASSERT_EQ(G.V[0].pathLen, 0);
  ASSERT_EQ(G.V[1].pathLen, 3);
  ASSERT_EQ(G.V[2].pathLen, 1);
  ASSERT_EQ(G.V[3].pathLen, 2);
  ASSERT_EQ(G.V[4].pathLen, 10);
}

TEST(BellmanFord, PosEdgesCycles) {
  Graph G(5);
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[1], 4));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[2], 1));
  G.E.emplace_back(make_tuple(&G.V[2], &G.V[1], 5));
  G.E.emplace_back(make_tuple(&G.V[2], &G.V[3], 1));
  G.E.emplace_back(make_tuple(&G.V[3], &G.V[1], 1));
  G.E.emplace_back(make_tuple(&G.V[3], &G.V[4], 8));
  G.E.emplace_back(make_tuple(&G.V[3], &G.V[0], 1));
  bool thereAreNotNegativeCycles = BellmanFord(G, 0);

  ASSERT_EQ(thereAreNotNegativeCycles, true);
  ASSERT_EQ(G.V[0].pathLen, 0);
  ASSERT_EQ(G.V[1].pathLen, 3);
  ASSERT_EQ(G.V[2].pathLen, 1);
  ASSERT_EQ(G.V[3].pathLen, 2);
  ASSERT_EQ(G.V[4].pathLen, 10);
}

TEST(BellmanFord, NegEdgesNoCycles) {
  Graph G(5);
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[1], -1));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[2], -5));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[4], -6));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[2], -4));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[4], -7));
  G.E.emplace_back(make_tuple(&G.V[2], &G.V[3], -6));
  G.E.emplace_back(make_tuple(&G.V[2], &G.V[4], -4));
  G.E.emplace_back(make_tuple(&G.V[3], &G.V[4], -2));
  bool thereAreNotNegativeCycles = BellmanFord(G, 0);

  ASSERT_EQ(thereAreNotNegativeCycles, true);
  ASSERT_EQ(G.V[0].pathLen, 0);
  ASSERT_EQ(G.V[1].pathLen, -1);
  ASSERT_EQ(G.V[2].pathLen, -5);
  ASSERT_EQ(G.V[3].pathLen, -11);
  ASSERT_EQ(G.V[4].pathLen, -13);
}

TEST(BellmanFord, NegEdgesNegCycles) {
  Graph G(5);
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[1], -1));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[2], -5));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[4], -6));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[2], -4));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[4], -7));
  G.E.emplace_back(make_tuple(&G.V[2], &G.V[3], -6));
  G.E.emplace_back(make_tuple(&G.V[3], &G.V[4], -2));
  G.E.emplace_back(make_tuple(&G.V[4], &G.V[3], -4));
  bool thereAreNotNegativeCycles = BellmanFord(G, 0);

  ASSERT_EQ(thereAreNotNegativeCycles, false);
}

TEST(BellmanFord, PosNegEdgesNoCycles) {
  Graph G(6);
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[1], -2));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[3], 3));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[5], 5));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[2], -3));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[5], 6));
  G.E.emplace_back(make_tuple(&G.V[4], &G.V[0], -10));
  G.E.emplace_back(make_tuple(&G.V[4], &G.V[2], -7));
  G.E.emplace_back(make_tuple(&G.V[5], &G.V[3], -2));
  bool thereAreNotNegativeCycles = BellmanFord(G, 0);

  ASSERT_EQ(thereAreNotNegativeCycles, true);
  ASSERT_EQ(G.V[0].pathLen, 0);
  ASSERT_EQ(G.V[1].pathLen, -2);
  ASSERT_EQ(G.V[2].pathLen, -5);
  ASSERT_EQ(G.V[3].pathLen, 2);
  ASSERT_EQ(G.V[4].pathLen, INT64_MAX);
  ASSERT_EQ(G.V[5].pathLen, 4);
}

TEST(BellmanFord, PosNegEdgesCycles) {
  Graph G(6);
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[1], -2));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[3], 3));
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[5], 5));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[2], -3));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[4], 12));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[5], 6));
  G.E.emplace_back(make_tuple(&G.V[4], &G.V[0], -10));
  G.E.emplace_back(make_tuple(&G.V[4], &G.V[2], -7));
  G.E.emplace_back(make_tuple(&G.V[5], &G.V[3], -2));
  bool thereAreNotNegativeCycles = BellmanFord(G, 0);

  ASSERT_EQ(thereAreNotNegativeCycles, true);
  ASSERT_EQ(G.V[0].pathLen, 0);
  ASSERT_EQ(G.V[1].pathLen, -2);
  ASSERT_EQ(G.V[2].pathLen, -5);
  ASSERT_EQ(G.V[3].pathLen, 2);
  ASSERT_EQ(G.V[4].pathLen, 10);
  ASSERT_EQ(G.V[5].pathLen, 4);
}

TEST(BellmanFord, PosNegEdgesNegCycles) {
  Graph G(5);
  G.E.emplace_back(make_tuple(&G.V[0], &G.V[1], 10));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[2], 3));
  G.E.emplace_back(make_tuple(&G.V[1], &G.V[3], 8));
  G.E.emplace_back(make_tuple(&G.V[3], &G.V[4], 9));
  G.E.emplace_back(make_tuple(&G.V[4], &G.V[1], -20));
  bool thereAreNotNegativeCycles = BellmanFord(G, 0);

  ASSERT_EQ(thereAreNotNegativeCycles, false);
}

TEST(Generator, Random) {
  auto now = chrono::system_clock::now();
  default_random_engine generator(now.time_since_epoch().count());
  uniform_int_distribution<int> distribution(1, 1e4);
  for (int i = 0; i < 1e2; ++i) {
    int vertNumInit = distribution(generator);
    int edgeNumInit = distribution(generator);
    auto G = generateGraph(vertNumInit, edgeNumInit);
    ASSERT_EQ(G.V.size(), vertNumInit);
    ASSERT_EQ(G.E.size(), edgeNumInit);
  }
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}