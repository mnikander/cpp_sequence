// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/sink/to_vector.hpp"
#include "../src/source/from_iota.hpp"
#include "../src/datatypes.hpp"

TEST(toVector, one)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0};

    // pipeline stages, from last to first
    auto sink     = to_vector(result);
    auto sequence = from_iota(sink);

    sequence.yield(1);
    EXPECT_EQ(result, expected);
}

TEST(toVector, five)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};

    // pipeline stages, from last to first
    auto sink     = to_vector(result);
    auto sequence = from_iota(sink);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(toVector, nested_pipeline)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};

    // pipeline, nested in order
    auto sequence =
        from_iota(
            to_vector(result));

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
