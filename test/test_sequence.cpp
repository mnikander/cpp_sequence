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

TEST(sequence, container_and_constant)
{
    using namespace sample;

    std::vector<int> const even{0, 2, 4, 6};
    auto glue = std::make_pair<int, int>;
    auto a    = get{even};
    auto b    = constant{42};
    auto const result = msp::sequence(glue, a, b)(2, -1);
    std::pair<int, int> const expected{4, 42};

    EXPECT_EQ(result, expected);
}

TEST(sequence, container_and_container)
{
    using namespace sample;

    std::vector<int> const even{0, 2, 4, 6};
    std::vector<int> const odd{1, 3, 5, 7};
    auto glue = std::make_pair<int, int>;
    auto a    = get{even};
    auto b    = get{odd};
    auto const result = msp::sequence(glue, a, b)(2, -1);
    std::pair<int, int> const expected{4, 5};

    EXPECT_EQ(result, expected);
}

TEST(sequence, recursive_add)
{
    using namespace sample;

    auto const result = msp::sequence{std::plus<>{}, msp::sequence{std::plus<>{}, get_result<int>{}, get_result<int>{}}, get_result<int>{}}(0, 1);
    EXPECT_EQ(result, 3);
}

TEST(sequence, recursive_pair)
{
    using namespace sample;

    auto const result = msp::sequence{std::make_pair<std::pair<int, int>, int>, msp::sequence{std::make_pair<int, int>, get_result<int>{}, get_result<int>{}}, get_result<int>{}}(0, 1);
    EXPECT_EQ(result, std::make_pair(std::make_pair(1, 1), 1));
}
