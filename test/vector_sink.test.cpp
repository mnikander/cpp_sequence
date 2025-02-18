// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/source/iota_source.hpp"
#include "../src/sink/vector_sink.hpp"

TEST(vector_sink, one)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto sequence = iota(sink);

    sequence.yield(1);
    EXPECT_EQ(result, expected);
}

TEST(vector_sink, five)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};

    // pipeline stages, from last to first
    auto sink     = toVector(result);
    auto sequence = iota(sink);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
