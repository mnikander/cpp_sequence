#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../src/example_functions.hpp"
#include "../src/example_predicates.hpp"
#include "../src/compose.hpp"

struct Empty
{
    bool operator==(Empty e) const { return true; }
};

struct return_empty
{
    using ResultType = Empty;

    template <typename T>
    Empty operator()(int i, T value) const
    {
        (void)i;
        (void)value;
        return Empty{};
    }
};

TEST(compose, nothing)
{
    auto const f     = msp::compose(return_empty{}, return_empty{});
    auto const result = f(0, 0);
    EXPECT_EQ(result, Empty{});
}

TEST(compose, increment)
{
    struct increment_value
    {
        using ResultType = int;

        ResultType operator()(int i, int value) const
        {
            (void)i;
            return value + 1;
        }
    };

    auto const f       = msp::compose(increment_value{}, increment_value{});
    int const result   = f(0, 0);
    EXPECT_EQ(result, 2);
}
