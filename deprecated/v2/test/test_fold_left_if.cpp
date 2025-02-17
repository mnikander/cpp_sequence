#include <gtest/gtest.h>
#include "../src/fold_left_if.hpp"
#include "../../../src/datatypes.hpp"

template <typename A, typename I, typename S>
bool always_false(A accumulator, I current, S sentinel)
{
    (void)accumulator;
    (void)current;
    (void)sentinel;
    return false;
}

template <typename A, typename I, typename S>
A plus(A accumulator, I current, S sentinel)
{
    (void)sentinel;
    return accumulator + current;
}

TEST(fold_left_if, integer_sum)
{
    using namespace seq;

    i32 result = fp::fold_left_if(plus<i32, i32, i32>, always_false<i32, i32, i32>, 0, 0, 5);
    EXPECT_EQ(result, 10);
}

template <typename A, typename I, typename S>
A plus_iter(A accumulator, I current, S sentinel)
{
    (void)sentinel;
    return accumulator + (*current);
}

TEST(fold_left_if, container_sum)
{
    using namespace seq;
    using iter = typename vi32::const_iterator;

    vi32 V{1, 2, 4, 8, 16};
    i32 result = fp::fold_left_if(plus_iter<i32, iter, iter>, always_false<i32, iter, iter>, 0, V.cbegin(), V.cend());
    EXPECT_EQ(result, 31);
}
