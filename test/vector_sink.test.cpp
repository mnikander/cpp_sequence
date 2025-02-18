// Copyright (c) 2025, Marco Nikander

#include <vector>
#include <gtest/gtest.h>
#include "../src/datatypes.hpp"
#include "../src/generator/iota_generator.hpp"
#include "../src/sink/vector_sink.hpp"

TEST(vector_sink, one)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0};

    // pipeline stages, from last to first
    auto sink     = make_vector_sink(result);
    auto sequence = make_iota_generator(sink);

    sequence.yield(1);
    EXPECT_EQ(result, expected);
}

TEST(vector_sink, five)
{
    using namespace seq;
    std::vector<i64> result{};
    std::vector<i64> const expected{0, 1, 2, 3, 4};

    // pipeline stages, from last to first
    auto sink     = make_vector_sink(result);
    auto sequence = make_iota_generator(sink);

    sequence.yield(5);
    EXPECT_EQ(result, expected);
}
