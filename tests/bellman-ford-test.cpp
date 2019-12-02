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

  ASSERT_EQ(thereAreNotNegativeCycles, true);
  ASSERT_EQ(G[0].pathLen, 0);
  ASSERT_EQ(G[1].pathLen, 3);
  ASSERT_EQ(G[2].pathLen, 1);
  ASSERT_EQ(G[3].pathLen, 2);
  ASSERT_EQ(G[4].pathLen, 10);
}

TEST(BellmanFord, PosEdgesCycles) {
    vector<Vertex> G(5);
    G[0].edges.emplace_back(make_pair(&G[1], 4));
    G[0].edges.emplace_back(make_pair(&G[2], 1));
    G[2].edges.emplace_back(make_pair(&G[1], 5));
    G[2].edges.emplace_back(make_pair(&G[3], 1));
    G[3].edges.emplace_back(make_pair(&G[1], 1));
    G[3].edges.emplace_back(make_pair(&G[4], 8));
    G[3].edges.emplace_back(make_pair(&G[0], 1));
    bool thereAreNotNegativeCycles = BellmanFord(G, 0);

    ASSERT_EQ(thereAreNotNegativeCycles, true);
    ASSERT_EQ(G[0].pathLen, 0);
    ASSERT_EQ(G[1].pathLen, 3);
    ASSERT_EQ(G[2].pathLen, 1);
    ASSERT_EQ(G[3].pathLen, 2);
    ASSERT_EQ(G[4].pathLen, 10);
}

TEST(BellmanFord, NegEdgesNoCycles) {
    vector<Vertex> G(5);
    G[0].edges.emplace_back(make_pair(&G[1], -1));
    G[0].edges.emplace_back(make_pair(&G[2], -5));
    G[0].edges.emplace_back(make_pair(&G[4], -6));
    G[1].edges.emplace_back(make_pair(&G[2], -4));
    G[1].edges.emplace_back(make_pair(&G[4], -7));
    G[2].edges.emplace_back(make_pair(&G[3], -6));
    G[2].edges.emplace_back(make_pair(&G[4], -4));
    G[3].edges.emplace_back(make_pair(&G[4], -2));
    bool thereAreNotNegativeCycles = BellmanFord(G, 0);

    ASSERT_EQ(thereAreNotNegativeCycles, true);
    ASSERT_EQ(G[0].pathLen, 0);
    ASSERT_EQ(G[1].pathLen, -1);
    ASSERT_EQ(G[2].pathLen, -5);
    ASSERT_EQ(G[3].pathLen, -11);
    ASSERT_EQ(G[4].pathLen, -13);
}

TEST(BellmanFord, NegEdgesNegCycles) {
    vector<Vertex> G(5);
    G[0].edges.emplace_back(make_pair(&G[1], -1));
    G[0].edges.emplace_back(make_pair(&G[2], -5));
    G[0].edges.emplace_back(make_pair(&G[4], -6));
    G[1].edges.emplace_back(make_pair(&G[2], -4));
    G[1].edges.emplace_back(make_pair(&G[4], -7));
    G[2].edges.emplace_back(make_pair(&G[3], -6));
    G[3].edges.emplace_back(make_pair(&G[4], -2));
    G[4].edges.emplace_back(make_pair(&G[3], -4));
    bool thereAreNotNegativeCycles = BellmanFord(G, 0);

    ASSERT_EQ(thereAreNotNegativeCycles, false);
}

TEST(BellmanFord, PosNegEdgesNoCycles) {
    vector<Vertex> G(6);
    G[0].edges.emplace_back(make_pair(&G[1], -2));
    G[0].edges.emplace_back(make_pair(&G[3], 3));
    G[0].edges.emplace_back(make_pair(&G[5], 5));
    G[1].edges.emplace_back(make_pair(&G[2], -3));
    G[1].edges.emplace_back(make_pair(&G[5], 6));
    G[4].edges.emplace_back(make_pair(&G[0], -10));
    G[4].edges.emplace_back(make_pair(&G[2], -7));
    G[5].edges.emplace_back(make_pair(&G[3], -2));
    bool thereAreNotNegativeCycles = BellmanFord(G, 0);

    ASSERT_EQ(thereAreNotNegativeCycles, true);
    ASSERT_EQ(G[0].pathLen, 0);
    ASSERT_EQ(G[1].pathLen, -2);
    ASSERT_EQ(G[2].pathLen, -5);
    ASSERT_EQ(G[3].pathLen, 2);
    ASSERT_EQ(G[4].pathLen, INT64_MAX);
    ASSERT_EQ(G[5].pathLen, 4);
}

TEST(BellmanFord, PosNegEdgesCycles) {
    vector<Vertex> G(6);
    G[0].edges.emplace_back(make_pair(&G[1], -2));
    G[0].edges.emplace_back(make_pair(&G[3], 3));
    G[0].edges.emplace_back(make_pair(&G[5], 5));
    G[1].edges.emplace_back(make_pair(&G[2], -3));
    G[1].edges.emplace_back(make_pair(&G[4], 12));
    G[1].edges.emplace_back(make_pair(&G[5], 6));
    G[4].edges.emplace_back(make_pair(&G[0], -10));
    G[4].edges.emplace_back(make_pair(&G[2], -7));
    G[5].edges.emplace_back(make_pair(&G[3], -2));
    bool thereAreNotNegativeCycles = BellmanFord(G, 0);

    ASSERT_EQ(thereAreNotNegativeCycles, true);
    ASSERT_EQ(G[0].pathLen, 0);
    ASSERT_EQ(G[1].pathLen, -2);
    ASSERT_EQ(G[2].pathLen, -5);
    ASSERT_EQ(G[3].pathLen, 2);
    ASSERT_EQ(G[4].pathLen, 10);
    ASSERT_EQ(G[5].pathLen, 4);
}

TEST(BellmanFord, PosNegEdgesNegCycles) {
    vector<Vertex> G(5);
    G[0].edges.emplace_back(make_pair(&G[1], 10));
    G[1].edges.emplace_back(make_pair(&G[2], 3));
    G[1].edges.emplace_back(make_pair(&G[3], 8));
    G[3].edges.emplace_back(make_pair(&G[4], 9));
    G[4].edges.emplace_back(make_pair(&G[1], -20));
    bool thereAreNotNegativeCycles = BellmanFord(G, 0);

    ASSERT_EQ(thereAreNotNegativeCycles, false);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}