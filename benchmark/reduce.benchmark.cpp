#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <benchmark/benchmark.h>
#include "../src/sequence.hpp"

constexpr uint64_t SAMPLES = 1'000'000;

// for random seed 0
std::map<uint64_t, int> const expected{
    std::make_pair(1'000u, 2'048),
    std::make_pair(10'000u, 19'696),
    std::make_pair(100'000u, 199'696),
    std::make_pair(1'000'000u, 1'999'250)};

std::vector<int64_t> random_vector(uint64_t const count) {
    // std::random_device rd;
    std::mt19937 gen(0);
    std::uniform_int_distribution<> distrib(0, 9);
    std::vector<int64_t> result(count);

    for (uint64_t i = 0; i < count; ++i) {
        result[i] = distrib(gen);
    }

    return result;
}

int64_t sum_even(std::vector<int64_t> const& numbers) {
    int64_t sum = 0;
    for (uint64_t i = 0; i < numbers.size(); ++i) {
        if(numbers[i] % 2 == 0) {
            sum += numbers[i];
        }
    }
    return sum;
}

static void BM_for_loop(benchmark::State& state) {
    std::vector<int64_t> numbers = random_vector(SAMPLES);
    int64_t sum = 0;

    for (auto _ : state) {
        // this code gets timed
        sum = sum_even(numbers);
    }

    assert(sum == expected.at(SAMPLES)); // check that the result is correct
    // std::cout << sum << std::endl;
}

static void BM_sequence(benchmark::State& state) {
    using namespace seq;
    std::vector<i64> numbers = random_vector(SAMPLES);
    i64 sum = 0;

    for (auto _ : state) {
        // this code gets timed
        auto pipeline = from_iota(0ULL,
            map<uint64_t>([&numbers](uint64_t i){ return numbers[i]; },
                filter<i64>([](i64 i){ return i%2==0; },
                    reduce<i64>(std::plus<i64>{}, 0LL,
                        to_value(sum)))));
        pipeline.yield(SAMPLES);
    }

    assert(sum == expected.at(SAMPLES)); // check that the result is correct
}

// Register the function as a benchmark
BENCHMARK(BM_for_loop);
BENCHMARK(BM_sequence);
