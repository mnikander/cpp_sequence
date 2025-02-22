// Copyright (c) 2025, Marco Nikander

#include <gtest/gtest.h>
#include "../src/sink/to_value.hpp"
#include "../src/source/from_iota.hpp"
#include "../src/datatypes.hpp"

TEST(toValue, one)
{
    using namespace seq;
    i64 result{};
    i64 const expected{0};

    // pipeline stages, from last to first
    auto sink     = toValue(result);
    auto sequence = from_iota(sink);

    sequence.yield(1);
    EXPECT_EQ(result, expected);
}

TEST(toValue, five)
{
    using namespace seq;
    i64 result{};
    i64 const expected{4};

    // pipeline stages, from last to first
    auto sink     = toValue(result);
    auto sequence = from_iota(sink);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(toValue, nested_call)
{
    using namespace seq;
    i64 result{};
    i64 const expected{4};

    // pipeline, nested in order
    auto sequence = from_iota(toValue(result));

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
