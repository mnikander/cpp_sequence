#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../src/algorithm/to.hpp"
#include "../src/compose.hpp"
#include "../src/example_functions.hpp"
#include "../src/example_predicates.hpp"

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

struct increment_int_value
{
    using ResultType = int;

    ResultType operator()(int i, int value) const
    {
        (void)i;
        return value + 1;
    }
};

TEST(compose, nothing)
{
    using namespace msp;
    
    auto       f      = compose(return_empty{}, return_empty{});
    auto const result = f(0, 0);
    EXPECT_EQ(result, Empty{});
}

TEST(compose, increment)
{
    using namespace msp;
    
    struct increment_value
    {
        using ResultType = int;

        ResultType operator()(int i, int value) const
        {
            (void)i;
            return value + 1;
        }
    };

    auto      f      = compose(increment_value{}, increment_value{});
    int const result = f(0, 0);
    EXPECT_EQ(result, 2);
}

TEST(compose, map)
{
    using namespace msp;
    std::vector<int> output = {-1, -1, -1};

    auto map = compose{to{output}, increment_int_value{}};
    map(1, 42);

    EXPECT_EQ(output[0], -1);
    EXPECT_EQ(output[1], 43);
    EXPECT_EQ(output[2], -1);
}
