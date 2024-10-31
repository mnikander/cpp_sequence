#include <gtest/gtest.h>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include "../src/example_functions.hpp"
#include "../src/example_predicates.hpp"
#include "../src/iterate.hpp"
#include "../src/algorithm/fold_left.hpp"
#include "../src/algorithm/from.hpp"

TEST(iterate, nothing)
{
    using namespace msp;
    using namespace sample;

    auto              f      = iterate{less_than{0}, string_catenate{}};
    std::string const result = f(0, std::string{""});

    EXPECT_EQ(result, std::string(""));
}

TEST(iterate, five)
{
    using namespace msp;
    using namespace sample;

    auto              f      = iterate{less_than{5}, string_catenate{}};
    std::string const result = f(0, std::string{""});

    EXPECT_EQ(result, std::string("0 1 2 3 4 "));
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

TEST(iterate, plus_reduce)
{
    using namespace msp;
    using namespace sample;

    std::vector<int> const vec{1, 2, 4, 8, 16};
    auto      f      = from{vec, fold_left{std::plus<>{}, 0}};
    int const result = f(0, 0);

    EXPECT_EQ(result, 31);
}

TEST(iterate, max_reduce)
{
    using namespace msp;
    using namespace sample;

    std::vector<int> const vec{1, 2, 16, 4, 8};
    auto      f      = from{vec, fold_left{[](int l, int r){ return std::max(l, r); }, 0}};
    int const result = f(0, 0);

    EXPECT_EQ(result, 16);
}
