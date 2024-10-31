#pragma once

#include <string>

namespace sample {

template <typename ResultT>
struct constant
{
    using ResultType = ResultT;

    explicit constant(ResultType value) : _value{value} {}

    template <typename Arg>
    ResultType operator()(int i, Arg argument) const
    {
        (void)i;
        (void)argument;
        return _value;
    }

    ResultType const _value;
};

template <typename ResultT>
struct default_construct
{
    using ResultType = ResultT;

    template <typename Arg>
    ResultType operator()(int i, Arg argument) const
    {
        (void)i;
        (void)argument;
        return ResultType{};
    }
};

template <typename ResultT>
struct get_argument
{
    using ResultType = ResultT;

    template <typename Arg>
    ResultType operator()(int i, Arg argument) const
    {
        static_assert(std::is_same<Arg, ResultType>(),
                      "Arg must equal ResultType.");
        (void)i;
        return argument;
    }
};

struct to_string
{
    using ResultType = std::string;

    template <typename Arg>
    ResultType operator()(int i, Arg argument) const
    {
        (void)i;
        return std::to_string(argument);
    }
};

template <typename Container>
struct get
{
    using ResultType = typename Container::value_type;

    explicit get(Container const& container) : _container{container} {}

    template <typename Arg>
    ResultType operator()(int i, Arg argument) const
    {
        (void)argument;
        return _container[i];
    }

    Container const& _container;
};

}
