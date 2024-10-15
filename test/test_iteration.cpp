#include <gtest/gtest.h>
#include <iostream>

#include "../src/iteration.hpp"

std::string concatenate_value(int const i, std::string result)
{
    return result + std::to_string(i) + std::string(" ");
};

TEST(iterate, nothing)
{
    smp::for_loop_object zero{0, 0, std::string{""}};
    auto const iteration_result = smp::iterate(zero, concatenate_value);

    EXPECT_EQ(iteration_result, std::string(""));
}

TEST(iterate, five)
{
    smp::for_loop_object zeroToFive{0, 5, std::string{""}};
    auto const iteration_result = smp::iterate(zeroToFive, concatenate_value);

    EXPECT_EQ(iteration_result, std::string("0 1 2 3 4 "));
}
