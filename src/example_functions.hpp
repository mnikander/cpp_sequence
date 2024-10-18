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
        (void)i;
        return input;
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

}
