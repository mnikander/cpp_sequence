// Copyright (c) 2025, Marco Nikander

#include <array>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota_source.hpp"
#include "../src/sink/range_sink.hpp"
#include "../src/stage/map_stage.hpp"

TEST(map_stage, identity)
{
    using namespace seq;
    std::array<i64, 5> result{0, 0, 0, 0, 0};
    std::array<i64, 5> const expected{0, 1, 2, 3, 4};

    // pipeline stages, from last to first
    auto sink     = make_range_sink(result);
    auto square   = make_map_stage<i64 const>([](i64 const i){ return i; }, sink);
    auto sequence = make_iota_source(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(map_stage, square)
{
    using namespace seq;

    std::array<i64, 5> result{0, 0, 0, 0, 0};
    std::array<i64, 5> const expected{0, 1, 4, 9, 16};

    // pipeline stages, from last to first
    auto sink     = make_range_sink(result);
    auto square   = make_map_stage<i64 const>([](i64 const value){ return value*value; }, sink);
    auto sequence = make_iota_source(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(map_stage, int_to_float)
{
    using namespace seq;
    std::array<f64, 5> result{0.0, 0.0, 0.0, 0.0, 0.0};
    std::array<f64, 5> const expected{0.0, 1.0, 2.0, 3.0, 4.0};

    // pipeline stages, from last to first
    auto sink     = make_range_sink(result);
    auto square   = make_map_stage<i64 const>([](i64 const i){ return static_cast<f64>(i); }, sink);
    auto sequence = make_iota_source(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
