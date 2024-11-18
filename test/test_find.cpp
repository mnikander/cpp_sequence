#include <gtest/gtest.h>
#include "../src/fold_left_if.hpp"
#include "../src/global_datatypes.hpp"

template <typename T>
struct Result
{
    T _value;
    bool _keep_going{true};
};


template <typename A, typename I, typename S>
A return_current(A accumulator, I current, S sentinel)
{
    (void)accumulator;
    (void)sentinel;
    return A{current};
}

template <typename A, typename I, typename S>
bool is_four(A accumulator, I current, S sentinel)
{
    (void)sentinel;
    (void)current;
    accumulator._keep_going = accumulator._value != 4;
    return (accumulator._keep_going);
}

template <typename A, typename I, typename S>
bool is_four_iter(A accumulator, I current, S sentinel)
{
    (void)sentinel;
    (void)current;
    accumulator._keep_going = *(accumulator._value) != 4;
    return (accumulator._keep_going);
}

TEST(find, integer)
{
    Result<int> result = fp::fold_left_if(return_current<Result<int>, i32, i32>, is_four<Result<int>, i32, i32>, Result<int>{0}, 0, 6);
    EXPECT_EQ(result._value, 4);
}

TEST(find, container_empty)
{
    using iter = typename vi32::const_iterator;
    vi32 V{};
    Result<iter> result = fp::fold_left_if(return_current<Result<iter>, iter, iter>, is_four_iter<Result<iter>, iter, iter>, Result<iter>{V.cbegin()}, V.cbegin(), V.cend());

    iter const expected = V.cend();
    EXPECT_EQ(result._value, expected);
}

TEST(find, container_true)
{
    using iter = typename vi32::const_iterator;
    vi32 V{1, 2, 4, 8, 16};
    Result<iter> result = fp::fold_left_if(return_current<Result<iter>, iter, iter>, is_four_iter<Result<iter>, iter, iter>, Result<iter>{V.cbegin()}, V.cbegin(), V.cend());

    iter const expected = V.cbegin() + 2;
    EXPECT_EQ(result._value, expected);
}

TEST(find, container_false)
{
    using iter = typename vi32::const_iterator;
    vi32 V{1, 2};
    Result<iter> result = fp::fold_left_if(return_current<Result<iter>, iter, iter>, is_four_iter<Result<iter>, iter, iter>, Result<iter>{V.cbegin()}, V.cbegin(), V.cend());

    iter const expected = V.cend();
    EXPECT_EQ(result._value, expected);

    // this unit test fails, because when `current == sentinel` the accumulator
    // is no longer updated, so instead of returning `last` it returns one
    // before the last.
    
    // This case is problematic, because I don't want to run the risk of
    // dereferencing the past-the-end iterator. A`function` or a `predicate`
    // which uses the sentinel value / iterator will segfault for many
    // functions and predicates.
}
