#include <iostream>
#include <benchmark/benchmark.h>
#include "../src/sequence.hpp"

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    std::cout << "hello world" << std::endl;
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);
