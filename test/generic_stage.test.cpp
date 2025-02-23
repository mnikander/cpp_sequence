// Copyright (c) 2025, Marco Nikander

#include <array>
#include <gtest/gtest.h>
#include "../src/sink/to_range.hpp"
#include "../src/source/from_iota.hpp"
#include "../src/stage/generic/stage.hpp"
#include "../src/datatypes.hpp"

TEST(stage, map)
{
    // In this example we define a pipeline with the following stages:
    // - generate a sequence of integers
    // - map each value to its square
    // - write each result to an output range
    //
    // Then we execute the pipeline, to generate 5 values, by calling '.yield(5)' on it

    using namespace seq;

    std::array<i64, 5> result{0, 0, 0, 0, 0};
    std::array<i64, 5> expected{0, 1, 4, 9, 16};

    auto f_sq = [](auto emit, auto&& value) -> Status { return emit(value*value); };

    // pipeline stages, from last to first
    auto sink     = to_range(result);
    auto square   = stage<i64>(f_sq, sink);
    auto sequence = from_iota(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
