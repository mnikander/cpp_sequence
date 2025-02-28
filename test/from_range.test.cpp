// Copyright (c) 2025, Marco Nikander

#include <functional>
#include <vector>
#include <gtest/gtest.h>
#include "../src/sink/to_range.hpp"
#include "../src/sink/to_value.hpp"
#include "../src/source/from_range.hpp"
#include "../src/stage/filter.hpp"
#include "../src/stage/map.hpp"
#include "../src/stage/reduce.hpp"
#include "../src/stage/take.hpp"
#include "../src/datatypes.hpp"

TEST(from_range, sum)
{
    using namespace seq;
    std::vector<i64> const input{0, 1, 2, 4, 8};
    i64 result = 0;

    // pipeline stages, from last to first
    auto sink     = to_value(result);
    auto stage    = reduce<i64>(std::plus<i64>{}, 0L, sink);
    auto sequence = from_range(input.cbegin(), input.cend(), stage);

    sequence.yield(5);
    EXPECT_EQ(result, 15);
}

TEST(from_range, nested_pipeline)
{
    using namespace seq;
    std::vector<i64> const input{0, 1, 2, 4, 8};
    i64 result = 0;

    // pipeline, nested in order
    auto sequence =
        from_range(input,
            reduce<i64>(std::plus<i64>{}, 0L,
                to_value(result)));

    sequence.yield(5);
    EXPECT_EQ(result, 15);
}

TEST(from_range, map_filter_reduce) {
    using namespace seq;

    auto plusTwo = [](i64 i){ return i + 2; };
    auto isEven  = [](i64 i){ return i % 2 == 0; };
    std::vector<i64> const input{0, 1, 2, 4, 8};
    i64 result = 0;

    // pipeline, nested in order
    auto sequence =
        from_range(input,
            map<i64>(plusTwo,
                filter<i64>(isEven,
                    reduce<i64>(std::plus<i64>{}, 0L,
                        take<i64>(4,
                            to_value(result))))));
    sequence.run(); // sum of (2, 4, 6, 10)
    EXPECT_EQ(result, 22);
}
