#include <gtest/gtest.h>
#include <iostream>

#include "../src/example_functions.hpp"
#include "../src/iteration.hpp"

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
