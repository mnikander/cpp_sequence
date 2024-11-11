#include <gtest/gtest.h>

#include "../src/fold_left.hpp"
#include "../src/global_datatypes.hpp"

template <typename A, typename I>
bool always_true(A accumulator, I current, I sentinel)
{
    (void)accumulator;
    (void)current;
    (void)sentinel;
    return true;
}

template <typename A, typename I>
A plus(A accumulator, I current, I sentinel)
{
    (void)sentinel;
    return accumulator + current;
}

TEST(fold_left, integer_sum)
{
    i32 result = fp::fold_left(plus<i32, i32>, always_true<i32, i32>, 0, 0, 5);
    EXPECT_EQ(result, 10);
}

template <typename A, typename I>
A plus_iter(A accumulator, I current, I sentinel)
{
    (void)sentinel;
    return accumulator + (*current);
}

TEST(fold_left, container_sum)
{
    using iter = typename vi32::const_iterator;
    vi32 V{1, 2, 4, 8, 16};
    i32 result = fp::fold_left(plus_iter<i32, iter>, always_true<i32, iter>, 0, V.cbegin(), V.cend());
    EXPECT_EQ(result, 31);
}
