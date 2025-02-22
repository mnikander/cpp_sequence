// Copyright (c) 2025, Marco Nikander

#include <functional>
#include <gtest/gtest.h>
#include "../src/sink/to_range.hpp"
#include "../src/sink/to_value.hpp"
#include "../src/source/from_iota.hpp"
#include "../src/stage/filter.hpp"
#include "../src/stage/map.hpp"
#include "../src/stage/reduce.hpp"
#include "../src/datatypes.hpp"

TEST(reduce, sum)
{
    using namespace seq;
    i64 result = 0;
    i64 const expected = 10;

    // pipeline stages, from last to first
    auto sink     = toValue(result);
    auto square   = reduce<i64>(std::plus<i64>{}, 0LL, sink);
    auto sequence = from_iota(square);

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
        from_iota(
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
        from_iota(
            map<int>(minusThree,
                filter<int>(isEven,
                    reduce<int>(std::plus<int>{}, 0,
                        toValue(result)))));
    sequence.yield(8); // sum of (-2, 0, 2, 4)
    EXPECT_EQ(result, 4);
}
