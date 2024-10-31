#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../src/compose.hpp"
#include "../src/example_functions.hpp"
#include "../src/algorithm/from.hpp"
#include "../src/algorithm/to.hpp"

struct increment_int_value
{
    using ResultType = int;

    ResultType operator()(int i, int value) const
    {
        (void)i;
        return value + 1;
    }
};

TEST(from, container)
{
    using namespace sample;
    using namespace msp;

    std::vector<int> const vec{1, 2, 4, 8};

    auto              f      = msp::from{vec, to_string{}};
    std::string const result = f(0, -1);
    std::string const expected{"8"};

    EXPECT_EQ(result, expected);
}

TEST(from, map)
{
    using namespace msp;

    std::vector<int> const input    = {1, 2, 4, 8};
    std::vector<int> const expected = {2, 3, 5, 9};
    std::vector<int> output         = {-1, -1, -1, -1};

    auto       f      = from{input, compose{to{output}, increment_int_value{}}};
    auto const result = f(0, -1);

    EXPECT_EQ(output, expected);
}
