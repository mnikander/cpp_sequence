#include <gtest/gtest.h>
#include <iostream>

#include "../src/iteration.hpp"

struct string_catenate
{
    using ResultType = std::string;

    std::string operator()(int i, std::string result)
    {
        return std::move(result) + std::to_string(i) + std::string(" ");
    }
};

struct less_than
{
    using ResultType = bool;

    explicit less_than(int limit) : _limit{limit} {}
    
    template <typename T>
    bool operator()(int i, T result) const
    {
        (void)result;
        return i < _limit;
    }

    int const _limit;
};

TEST(iterate, nothing)
{
    auto const iteration_result = msp::iterate(less_than{0}, string_catenate{});

    EXPECT_EQ(iteration_result, std::string(""));
}

TEST(iterate, five)
{
    auto const iteration_result = msp::iterate(less_than{5}, string_catenate{});

    EXPECT_EQ(iteration_result, std::string("0 1 2 3 4 "));
}
