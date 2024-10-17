#include <gtest/gtest.h>
#include <iostream>

#include "../src/iteration.hpp"

struct catenate_value {
    template <typename LoopObject>
    std::string operator()(LoopObject loop)
    {
        return loop.result() + std::to_string(loop.state()) + std::string(" ");
    };
};

TEST(iterate, nothing)
{
    msp::for_loop_object zero{0, 0, std::string{""}};
    auto const iteration_result = msp::iterate(zero, catenate_value{});

    EXPECT_EQ(iteration_result, std::string(""));
}

TEST(iterate, five)
{
    msp::for_loop_object zeroToFive{0, 5, std::string{""}};
    auto const iteration_result = msp::iterate(zeroToFive, catenate_value{});

    EXPECT_EQ(iteration_result, std::string("0 1 2 3 4 "));
}
