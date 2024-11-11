#pragma once

#include <string>

namespace sample {

struct less_than
{
    using ResultType = bool;

    explicit less_than(int value) : _value{value} {}

    template <typename T>
    bool operator()(int i, T result) const
    {
        (void)result;
        return i < _value;
    }

    int const _value;
};

struct counter_equal_to
{
    using ResultType = bool;

    explicit counter_equal_to(int value) : _value{value} {}

    template <typename T>
    bool operator()(int i, T result) const
    {
        (void)result;
        return i == _value;
    }

    int const _value;
};

}
