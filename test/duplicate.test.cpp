// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/sink/to_vector.hpp"
#include "../src/source/from_iota.hpp"
#include "../src/stage/duplicate.hpp"
#include "../src/stage/take.hpp"
#include "../src/datatypes.hpp"

TEST(duplicate, nothing)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{};

    // pipeline stages, from last to first
    auto sink     = to_vector(result);
    auto echo     = duplicate<i64>(sink);
    auto sequence = from_iota(echo);

    sequence.yield(0);
    EXPECT_EQ(result, expected);
}

TEST(duplicate, double_sequence)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 0};

    // pipeline stages, from last to first
    auto sink     = to_vector(result);
    auto echo     = duplicate<i64>(2, sink);
    auto sequence = from_iota(echo);

    sequence.yield(1);
    EXPECT_EQ(result, expected);
}

TEST(duplicate, triple_sequence)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 0, 0};

    // pipeline stages, from last to first
    auto sink     = to_vector(result);
    auto echo     = duplicate<i64>(3, sink);
    auto sequence = from_iota(echo);

    sequence.yield(1);
    EXPECT_EQ(result, expected);
}

TEST(duplicate, five)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 0, 1, 1, 2, 2, 3, 3, 4, 4};

    // pipeline stages, from last to first
    auto sink     = to_vector(result);
    auto echo     = duplicate<i64>(sink);
    auto sequence = from_iota(echo);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(duplicate, nested_pipeline)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 0, 1, 1, 2, 2, 3, 3, 4, 4};

    // pipeline, nested in order
    auto sequence =
        from_iota(
            duplicate<i64>(2, 
                to_vector(result)));

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}

TEST(duplicate, halt_during_duplication)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 0, 0, 0, 1, 1, 1, 1, 2, 2};

    // pipeline, nested in order
    auto sequence =
        from_iota(
            duplicate<i64>(4,
                take<i64>(10,
                    to_vector(result))));

    sequence.run();
    EXPECT_EQ(result.size(), 10);
    EXPECT_EQ(result, expected);
}
