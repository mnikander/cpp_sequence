// Copyright (c) 2025, Marco Nikander

#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota.hpp"
#include "../src/sink/value_sink.hpp"

TEST(toValue, one)
{
    using namespace seq;
    i64 result{};
    i64 const expected{0};

    // pipeline stages, from last to first
    auto sink     = toValue(result);
    auto sequence = iota(sink);

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
    auto sequence = iota(sink);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(toValue, nested_call)
{
    using namespace seq;
    i64 result{};
    i64 const expected{4};

    // pipeline, nested in order
    auto sequence = iota(toValue(result));

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
