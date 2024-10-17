#include <gtest/gtest.h>
#include <functional>
#include <utility>

#include "../src/example_functions.hpp"
#include "../src/sequence.hpp"

TEST(sequence, nothing)
{
    using namespace sample;

    int const result = msp::sequence{std::plus<>{}, default_construct<int>{}, default_construct<int>{}}(2, 4);

    EXPECT_EQ(result, 0);
}

TEST(sequence, add)
{
    using namespace sample;

    int const result = msp::sequence{std::plus<>{}, get_result<int>{}, get_result<int>{}}(0, 42);

    EXPECT_EQ(result, 84);
}

TEST(sequence, pair)
{
    using namespace sample;

    auto const result = msp::sequence{std::make_pair<int, int>, default_construct<int>{}, default_construct<int>{}}(2, 4);

    EXPECT_EQ(result, std::make_pair(0, 0));
}
