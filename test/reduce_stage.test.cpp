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
    auto sink     = make_value_sink(result);
    auto square   = make_reduce_stage<i64>(std::plus<i64>{}, 0LL, sink);
    auto sequence = make_iota_source(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
