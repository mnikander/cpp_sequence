#pragma once

#include <string>

namespace sample {

template <typename ResultT>
struct constant
{
    using ResultType = ResultT;

    explicit constant(ResultType value) : _value{value} {}

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        (void)i;
        (void)input;
        return _value;
    }

    ResultType const _value;
};

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
        (void)i;
        return input;
    }
};

struct to_string
{
    using ResultType = std::string;

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        return std::to_string(input);
    }
};

struct string_catenate
{
    using ResultType = std::string;

    ResultType operator()(int i, std::string input) const
    {
        return std::move(input) + std::to_string(i) + std::string(" ");
    }
};

template <typename Container>
struct get
{
    using ResultType = typename Container::value_type;

    explicit get(Container container) : _container{container} {}

    template <typename InputType>
    ResultType operator()(int i, InputType input) const
    {
        (void)input;
        return _container[i];
    }

    Container _container;
};

template <typename F, typename T>
struct accumulator
{
    using ResultType = T;

    explicit accumulator(F binary_function, T initial_value) : _binary_function{binary_function}, _value{initial_value} {}

    template <typename InputType>
    ResultType operator()(int i, InputType input)
    {
        (void)i;
        return _value = _binary_function(_value, input);
    }

    // mutable state means this code is not referentially transparent :(
    F _binary_function;
    T _value;
};

}
