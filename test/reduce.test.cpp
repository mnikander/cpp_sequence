// Copyright (c) 2025, Marco Nikander

#include <functional>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota_source.hpp"
#include "../src/sink/range_sink.hpp"
#include "../src/sink/value_sink.hpp"
#include "../src/stage/filter_stage.hpp"
#include "../src/stage/map_stage.hpp"
#include "../src/stage/reduce_stage.hpp"

TEST(reduce, sum)
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

TEST(reduce, nested_pipeline)
{
    using namespace seq;
    i64 result = 0;
    i64 const expected = 10;

    // pipeline, nested in order
    auto sequence =
        iota(
            reduce<i64>(std::plus<i64>{}, 0LL,
                toValue(result)));

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(reduce, map_filter_reduce) {
    using namespace seq;

    auto minusThree = [](int i){ return i - 3; };
    auto isEven     = [](int i){ return i % 2 == 0; };
    int result = 0;

    // pipeline, nested in order
    auto sequence =
        iota(
            map<int>(minusThree,
                filter<int>(isEven,
                    reduce<int>(std::plus<int>{}, 0,
                        toValue(result)))));
    sequence.yield(8); // sum of (-2, 0, 2, 4)
    EXPECT_EQ(result, 4);
}
