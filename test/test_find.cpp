#include <gtest/gtest.h>
#include "../src/fold_left_if.hpp"
#include "../src/global_datatypes.hpp"

template <typename A, typename I, typename S>
A return_current(A accumulator, I current, S sentinel)
{
    (void)accumulator;
    (void)sentinel;
    return current;
}

template <typename A, typename I, typename S>
bool is_four(A accumulator, I current, S sentinel)
{
    (void)accumulator;
    (void)sentinel;
    return current == 4;
}

template <typename A, typename I, typename S>
bool is_four_iter(A accumulator, I current, S sentinel)
{
    (void)accumulator;
    (void)sentinel;
    return *current == 4;
}

TEST(find, integer)
{
    i32 result = fp::fold_left_if(return_current<i32, i32, i32>, is_four<i32, i32, i32>, 0, 0, 6);
    EXPECT_EQ(result, 4);
}

TEST(find, container)
{
    using iter = typename vi32::const_iterator;
    vi32 V{1, 2, 4, 8, 16};
    iter result = fp::fold_left_if(return_current<iter, iter, iter>, is_four_iter<iter, iter, iter>, V.cbegin(), V.cbegin(), V.cend());
    
    iter const expected = V.cbegin() + 2;
    EXPECT_EQ(result, expected);
}
