// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota_source.hpp"
#include "../src/sink/vector_sink.hpp"
#include "../src/stage/filter_stage.hpp"
#include "../src/stage/map_stage.hpp"
#include "../src/stage/take_stage.hpp"


TEST(take_stage, zero)
{
    using namespace seq;
    std::vector<i64> result{};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto take0    = take<i64>(0, sink);
    auto sequence = iota(take0);
    sequence.run();
    EXPECT_EQ(result.size(), 0);
}

TEST(take_stage, one)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto take1    = take<i64>(1, sink);
    auto sequence = iota(take1);
    sequence.run();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result, expected);
}

TEST(take_stage, two)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto take2    = take<i64>(2, sink);
    auto sequence = iota(take2);
    sequence.run();
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result, expected);
}

TEST(take_stage, five)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto take5    = take<i64>(5, sink);
    auto sequence = iota(take5);
    sequence.run();
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result, expected);
}

TEST(take_stage, halt_and_attempt_restart)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto take2    = take<i64>(2, sink);
    auto sequence = iota(take2);
    sequence.run(); // get 2 values
    sequence.run(); // attempt to restart the pipeline: it should NOT start
    sequence.yield(2); // attempt to restart via yield: it should NOT start
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result, expected);
}

TEST(take_stage, map_three_numbers)
{
    using namespace seq;
    std::vector<i64> const expected{0, 1, 4};
    std::vector<i64> result{};
    auto square = [](int value){ return value*value; };

    // define the pipeline stages, from last to first
    auto sink     = toVector(result);          // write each result
    auto take3    = take<int>(3, sink);        // HALT after 3 elements
    auto map_sq   = map<int>(square, take3);   // square each element
    auto sequence = iota(map_sq);              // generate integers [0, inf)

    // run the pipeline until one of the stages signals HALT
    sequence.run();
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result, expected);
}

TEST(take_stage, three_even_numbers)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 2, 4};
    auto isEven = [](i64 i) {return i % 2 == 0; };

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto take3    = take<i64>(3, sink);
    auto filterEv = filter<i64>(isEven, take3);
    auto sequence = iota(filterEv);
    sequence.run();
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result, expected);
}

TEST(take_stage, nested_call)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 2, 4};
    auto isEven = [](i64 i) {return i % 2 == 0; };

    // pipeline, nested in order
    auto sequence =
        iota(
            filter<i64>(isEven,
                take<i64>(3,
                    toVector(result))));
    sequence.run();
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result, expected);
}
