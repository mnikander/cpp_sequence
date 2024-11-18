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

TEST(find, container_empty)
{
    using iter = typename vi32::const_iterator;
    vi32 V{};
    iter result = fp::fold_left_if(return_current<iter, iter, iter>, is_four_iter<iter, iter, iter>, V.cbegin(), V.cbegin(), V.cend());

    iter const expected = V.cend();
    EXPECT_EQ(result, expected);
}

TEST(find, container_true)
{
    using iter = typename vi32::const_iterator;
    vi32 V{1, 2, 4, 8, 16};
    iter result = fp::fold_left_if(return_current<iter, iter, iter>, is_four_iter<iter, iter, iter>, V.cbegin(), V.cbegin(), V.cend());

    iter const expected = V.cbegin() + 2;
    EXPECT_EQ(result, expected);
}

TEST(find, container_false)
{
    using iter = typename vi32::const_iterator;
    vi32 V{1, 2};
    iter result = fp::fold_left_if(return_current<iter, iter, iter>, is_four_iter<iter, iter, iter>, V.cbegin(), V.cbegin(), V.cend());

    iter const expected = V.cend();
    EXPECT_EQ(result, expected);

    // this unit test fails, because when `current == sentinel` the accumulator
    // is no longer updated, so instead of returning `last` it returns one
    // before the last.
    
    // This case is problematic, because I don't want to run the risk of
    // dereferencing the past-the-end iterator. A`function` or a `predicate`
    // which uses the sentinel value / iterator will segfault for many
    // functions and predicates.
}
