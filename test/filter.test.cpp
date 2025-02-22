// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota_source.hpp"
#include "../src/sink/vector_sink.hpp"
#include "../src/stage/filter_stage.hpp"

TEST(filter, all)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};
    auto alwaysTrue = [](i64 const i){ (void)i; return true; };

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto square   = filter<i64>(alwaysTrue, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(filter, none)
{
    using namespace seq;
    std::vector<i64> result{};
    auto alwaysFalse = [](i64 const i){ (void)i; return false; };

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto square   = filter<i64>(alwaysFalse, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    ASSERT_EQ(result.size(), 0);
}

TEST(filter, one)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{1};
    auto isOne = [](i64 const i){ return i == 1; };

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto square   = filter<i64>(isOne, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result, expected);
}

TEST(filter, even)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 2, 4};
    auto isEven = [](i64 const i){ return i % 2 == 0; };

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto square   = filter<i64>(isEven, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result, expected);
}

TEST(filter, nested_pipeline)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 2, 4};
    auto isEven = [](i64 const i){ return i % 2 == 0; };

    // pipeline, nested in order
    auto sequence =
        iota(
            filter<i64>(isEven,
                toVector(result)));

    sequence.yield(5);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result, expected);
}
