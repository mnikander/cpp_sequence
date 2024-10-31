#include <gtest/gtest.h>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include "../src/algorithm/from.hpp"
#include "../src/algorithm/get.hpp"
#include "../src/example_functions.hpp"
#include "../src/example_predicates.hpp"
#include "../src/iterate.hpp"

TEST(iterate, nothing)
{
    using namespace msp;
    using namespace sample;

    auto              f      = iterate{less_than{0}, to_string{}};
    std::string const result = f(0, ' ');

    EXPECT_EQ(result, std::string(""));
}

TEST(iterate, five)
{
    using namespace msp;
    using namespace sample;

    auto              f      = iterate{less_than{5}, to_string{}};
    std::string const result = f(0, 0);

    EXPECT_EQ(result, "0");
}

TEST(iterate, container)
{
    using namespace msp;
    using namespace sample;

    std::vector<int> const vec{1, 2, 4, 8};
    auto condition   = less_than{static_cast<int>(vec.size())};
    auto getter      = get{vec};
    auto f           = iterate{condition, getter};
    int const result = f(0, -1);
    int const expected{8};

    EXPECT_EQ(result, expected);
}
