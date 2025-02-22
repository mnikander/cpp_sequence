// Copyright (c) 2025, Marco Nikander

#include <array>
#include <vector>
#include <gtest/gtest.h>
#include "../src/sink/to_range.hpp"
#include "../src/sink/to_vector.hpp"
#include "../src/source/from_iota.hpp"
#include "../src/stage/map.hpp"
#include "../src/datatypes.hpp"

TEST(map, identity)
{
    using namespace seq;
    std::array<i64, 5> result{0, 0, 0, 0, 0};
    std::array<i64, 5> const expected{0, 1, 2, 3, 4};

    // pipeline stages, from last to first
    auto sink     = toRange(result);
    auto square   = map<i64 const>([](i64 const i){ return i; }, sink);
    auto sequence = from_iota(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(map, square)
{
    using namespace seq;

    std::array<i64, 5> result{0, 0, 0, 0, 0};
    std::array<i64, 5> const expected{0, 1, 4, 9, 16};

    // pipeline stages, from last to first
    auto sink     = toRange(result);
    auto square   = map<i64 const>([](i64 const value){ return value*value; }, sink);
    auto sequence = from_iota(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(map, int_to_float)
{
    using namespace seq;
    std::array<f64, 5> result{0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<f64, 5> const expected{0.0, 1.0, 2.0, 3.0, 4.0};

    // pipeline stages, from last to first
    auto sink     = toRange(result);
    auto square   = map<i64 const>([](i64 const i){ return static_cast<f64>(i); }, sink);
    auto sequence = from_iota(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(map, nested_call)
{
    using namespace seq;

    std::vector<int> const expected{0, 1, 4, 9, 16};
    std::vector<int> result{};
    auto squared = [](int value){ return value*value; };

    // pipeline, nested in order
    auto pipeline = from_iota(map<int>(squared, toVector(result)));

    // run the pipeline to produce the first 5 values
    pipeline.yield(5);

    ASSERT_EQ(result.size(), 5);
    EXPECT_EQ(result, expected);
}
