// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota_source.hpp"
#include "../src/sink/vector_sink.hpp"
#include "../src/stage/filter_stage.hpp"

TEST(filter_stage, all)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto square   = filter<i64>([](i64 const i){ (void)i; return true; }, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(filter_stage, none)
{
    using namespace seq;
    std::vector<i64> result{};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto square   = filter<i64>([](i64 const i){ (void)i; return false; }, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    ASSERT_EQ(result.size(), 0);
}

TEST(filter_stage, one)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{1};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto square   = filter<i64>([](i64 const i){ return i == 1; }, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result, expected);
}

TEST(filter_stage, even)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 2, 4};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto square   = filter<i64>([](i64 const i){ return i % 2 == 0; }, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result, expected);
}
