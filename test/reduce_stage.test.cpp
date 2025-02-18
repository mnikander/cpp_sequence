// Copyright (c) 2025, Marco Nikander

#include <functional>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/generator/iota_generator.hpp"
#include "../src/sink/range_sink.hpp"
#include "../src/sink/value_sink.hpp"
#include "../src/stage/reduce_stage.hpp"

TEST(reduce_stage, sum)
{
    using namespace seq;
    mutable_i64 result = 0;
    i64 expected = 10;

    // pipeline stages, from last to first
    auto sink     = make_value_sink(result);
    auto square   = make_reduce_stage<mutable_i64>(std::plus<mutable_i64>{}, 0LL, sink);
    auto sequence = make_iota_generator(square);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
