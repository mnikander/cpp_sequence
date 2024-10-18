#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../src/example_functions.hpp"
#include "../src/example_predicates.hpp"
#include "../src/iterate.hpp"

TEST(iterate, nothing)
{
    using namespace sample;

    auto const f             = msp::iterate{less_than{0}, string_catenate{}};
    std::string const result = f(0, std::string{""});

    EXPECT_EQ(result, std::string(""));
}

TEST(iterate, five)
{
    using namespace sample;

    auto const f             = msp::iterate{less_than{5}, string_catenate{}};
    std::string const result = f(0, std::string{""});

    EXPECT_EQ(result, std::string("0 1 2 3 4 "));
}

TEST(iterate, container)
{
    using namespace sample;

    std::vector<int> const vec{1, 2, 4, 8};
    auto condition   = less_than{static_cast<int>(vec.size())};
    auto getter      = get{vec};
    auto const f     = msp::iterate(condition, getter);
    int const result = f(0, -1);
    int const expected{8};

    EXPECT_EQ(result, expected);
}
