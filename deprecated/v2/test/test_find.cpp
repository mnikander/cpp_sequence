#include <gtest/gtest.h>
#include "../src/fold_left_if.hpp"
#include "../../../src/datatypes.hpp"

template <typename I>
I assign_if_four(I accumulator, I current, I sentinel)
{
    (void)accumulator;
    (void)sentinel;
    return current == 4 ? current : accumulator;
}

template <typename I, typename S>
I assign_if_four_iter(I accumulator, I current, S sentinel)
{
    (void)accumulator;
    (void)sentinel;
    return *current == 4 ? current : accumulator;
}

template <typename A, typename I, typename S>
bool is_found(A accumulator, I current, S sentinel)
{
    (void)current;
    return accumulator != sentinel;
}

TEST(find, integer)
{
    using namespace seq;
    i32 const result = fp::fold_left_if(assign_if_four<i32 const>, is_found<i32 const, i32 const, i32 const>, 6, 0, 6);
    EXPECT_EQ(result, 4);
}

TEST(find, container_empty)
{
    using namespace seq;
    using iter = typename vi32::const_iterator;
    vi32 const V{};
    iter result = fp::fold_left_if(assign_if_four_iter<iter, iter>, is_found<iter, iter, iter>, V.cend(), V.cbegin(), V.cend());

    iter const expected = V.cend();
    EXPECT_EQ(result, expected);
}

TEST(find, container_true)
{
    using namespace seq;
    using iter = typename vi32::const_iterator;
    vi32 const V{1, 2, 4, 8, 16};
    iter result = fp::fold_left_if(assign_if_four_iter<iter, iter>, is_found<iter, iter, iter>, V.cend(), V.cbegin(), V.cend());

    iter const expected = V.cbegin() + 2;
    EXPECT_EQ(result, expected);
}

TEST(find, container_false)
{
    using namespace seq;
    using iter = typename vi32::const_iterator;
    vi32 const V{1, 2};
    iter result = fp::fold_left_if(assign_if_four_iter<iter, iter>, is_found<iter, iter, iter>, V.cend(), V.cbegin(), V.cend());

    iter const expected = V.cend();
    EXPECT_EQ(result, expected);
}
