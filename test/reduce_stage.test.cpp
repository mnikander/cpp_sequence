// Copyright (c) 2025, Marco Nikander

#include <functional>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota_source.hpp"
#include "../src/sink/range_sink.hpp"
#include "../src/sink/value_sink.hpp"
#include "../src/stage/reduce_stage.hpp"

TEST(reduce_stage, sum)
{
    using namespace seq;
    i64 result = 0;
    i64 const expected = 10;

    // pipeline stages, from last to first
    auto sink     = toValue(result);
    auto square   = reduce<i64>(std::plus<i64>{}, 0LL, sink);
    auto sequence = iota(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(reduce_stage, nested_pipeline)
{
    using namespace seq;
    i64 result = 0;
    i64 const expected = 10;

    // pipeline stages, nested in order
    auto sequence = iota(reduce<i64>(std::plus<i64>{}, 0LL, toValue(result)));

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
