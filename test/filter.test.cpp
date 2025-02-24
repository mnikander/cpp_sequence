// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/sink/to_vector.hpp"
#include "../src/source/from_iota.hpp"
#include "../src/stage/filter.hpp"
#include "../src/datatypes.hpp"

TEST(filter, all)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};
    auto alwaysTrue = [](i64 const i){ (void)i; return true; };

    // pipeline stages, from last to first
    auto sink     = to_vector(result);
    auto stage    = filter<i64>(alwaysTrue, sink);
    auto sequence = from_iota(stage);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(filter, none)
{
    using namespace seq;
    std::vector<i64> result{};
    auto alwaysFalse = [](i64 const i){ (void)i; return false; };

    // pipeline stages, from last to first
    auto sink     = to_vector(result);
    auto stage    = filter<i64>(alwaysFalse, sink);
    auto sequence = from_iota(stage);

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
    auto sink     = to_vector(result);
    auto stage    = filter<i64>(isOne, sink);
    auto sequence = from_iota(stage);

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
    auto sink     = to_vector(result);
    auto stage    = filter<i64>(isEven, sink);
    auto sequence = from_iota(stage);

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
        from_iota(
            filter<i64>(isEven,
                to_vector(result)));

    sequence.yield(5);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result, expected);
}
