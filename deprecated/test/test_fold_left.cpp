#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "../src/algorithm/fold_left.hpp"
#include "../src/algorithm/from.hpp"

TEST(fold_left, plus)
{
    using namespace msp;
    using namespace sample;

    std::vector<int> const vec{1, 2, 4, 8, 16};
    auto      f      = from{vec, fold_left{std::plus<>{}, 0}};
    int const result = f(0, 0);

    EXPECT_EQ(result, 31);
}

TEST(fold_left, max)
{
    using namespace msp;
    using namespace sample;

    std::vector<int> const vec{1, 2, 16, 4, 8};
    auto      f      = from{vec, fold_left{[](int l, int r){ return std::max(l, r); }, 0}};
    int const result = f(0, 0);

    EXPECT_EQ(result, 16);
}

TEST(fold_left, string_catenate)
{
    using namespace msp;
    
    std::vector<char> const input  = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    auto                    f      = from{input, fold_left{[](auto l, auto r){ return l + r; }, std::string("")}};
    std::string const       result = f(0, 0);
    EXPECT_EQ(result, std::string("hello world"));
}
