#include <gtest/gtest.h>
#include <iostream>

#include "../src/example_functions.hpp"
#include "../src/example_predicates.hpp"
#include "../src/iterate.hpp"

TEST(iterate, nothing)
{
    using namespace sample;

    auto const iteration_result = msp::iterate{less_than{0}, string_catenate{}}(0, std::string{""});

    EXPECT_EQ(iteration_result, std::string(""));
}

TEST(iterate, five)
{
    using namespace sample;

    auto const iteration_result = msp::iterate{less_than{5}, string_catenate{}}(0, std::string{""});

    EXPECT_EQ(iteration_result, std::string("0 1 2 3 4 "));
}

TEST(iterate, container)
{
    using namespace sample;

    std::vector<int> const vec{1, 2, 4, 8};
    auto condition   = less_than{static_cast<int>(vec.size())};
    auto getter      = get{vec};
    int const result = msp::iterate(condition, getter)(0, -1);
    int const expected{8};

    EXPECT_EQ(result, expected);
}
