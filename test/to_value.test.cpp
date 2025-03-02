// Copyright (c) 2025, Marco Nikander

#include <gtest/gtest.h>
#include "../src/sink/to_value.hpp"
#include "../src/source/from_iota.hpp"
#include "../src/datatypes.hpp"

TEST(to_value, one)
{
    using namespace seq;
    i64 result{};
    i64 const expected{0};

    // pipeline stages, from last to first
    auto sink     = to_value(result);
    auto sequence = from_iota(sink);

    sequence.yield(1);
    EXPECT_EQ(result, expected);
}

TEST(to_value, five)
{
    using namespace seq;
    i64 result{};
    i64 const expected{4};

    // pipeline stages, from last to first
    auto sink     = to_value(result);
    auto sequence = from_iota(sink);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(to_value, nested_call)
{
    using namespace seq;
    i64 result{};
    i64 const expected{4};

    // pipeline, nested in order
    auto sequence = from_iota(to_value(result));

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
