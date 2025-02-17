#include <array>
#include <gtest/gtest.h>
#include "../src/stage.hpp"
#include "../src/sink.hpp"
#include "../src/emit.hpp"
#include "../src/generator.hpp"

TEST(sequence, map)
{
    // In this example we define a pipeline with the following stages:
    // - generate a sequence of integers (starts at 0, by definition)
    // - map each value to its square
    // - write each result to an output range
    //
    // Then we execute the pipeline, to generate 5 values, by calling '.yield(5)' on it

    using namespace seq;

    std::array<mut_i64, 5> result{0, 0, 0, 0, 0};
    std::array<mut_i64, 5> expected{0, 1, 4, 9, 16};

    auto f_id = [](auto emit, auto&& value)->void { emit(std::move(value)); };
    auto f_sq = [](auto emit, auto&& value)->void { emit(value*value); };

    RangeSink sink{result};
    auto square = make_stage<mut_i64>(f_sq, sink);
    auto sequence = make_generator(f_id, square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
