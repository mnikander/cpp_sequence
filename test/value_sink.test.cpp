// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota_source.hpp"
#include "../src/sink/value_sink.hpp"

TEST(value_sink, one)
{
    using namespace seq;
    i64 result{};
    i64 const expected{0};

    // pipeline stages, from last to first
    auto sink     = make_value_sink(result);
    auto sequence = make_iota_source(sink);

    sequence.yield(1);
    EXPECT_EQ(result, expected);
}

TEST(value_sink, five)
{
    using namespace seq;
    i64 result{};
    i64 const expected{4};

    // pipeline stages, from last to first
    auto sink     = make_value_sink(result);
    auto sequence = make_iota_source(sink);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
