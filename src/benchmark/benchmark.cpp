//
// Created by sergo on 12/8/19.
//

#include <benchmark/benchmark.h>
#include "bellman-ford.cpp"
#include "generator.cpp"

static void BM_BellmanFord(benchmark::State &state) {
  for (auto _: state) {
    state.PauseTiming();
    auto G = generateGraph(state.range(0), state.range(1));
    state.ResumeTiming();
    bool negativeCycle = BellmanFord(G, 0);
  }
}

static void CustomArguments(benchmark::internal::Benchmark* b) {
  for (int i = 1e2; i <= (100 << 4); i *= 2)
    for (int j = 100 << 5; j <= (100 << 10); j *= 2)
      b->Args({i, j});
}

BENCHMARK(BM_BellmanFord)
    ->Apply(CustomArguments)
    ->Iterations(10);


BENCHMARK_MAIN();
