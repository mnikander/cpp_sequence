#pragma once

#include <string>

namespace sample {

template <typename ResultT>
struct default_construct
{
    using ResultType = ResultT;

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        (void)i;
        (void)input;
        return ResultType{};
    }
};

template <typename ResultT>
struct get_result
{
    using ResultType = ResultT;

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        static_assert(std::is_same<InputType, ResultType>(),
                      "InputType must equal ResultType.");
        return input;
    }
};

struct string_catenate
{
    using ResultType = std::string;

    std::string operator()(int i, std::string input) const
    {
        return std::move(input) + std::to_string(i) + std::string(" ");
    }
};

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

struct equal_to
{
    using ResultType = bool;

    explicit equal_to(int value) : _value{value} {}

    template <typename T>
    bool operator()(int i, T result) const
    {
        (void)result;
        return i == _value;
    }

    int const _value;
};

}