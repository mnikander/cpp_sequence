#pragma once

namespace msp {

template <typename F, typename T>
struct fold_left
{
    using ResultType = T;

    explicit fold_left(F binary_function, T initial_value) : _binary_function{binary_function}, _value{initial_value} {}

    template <typename InputType>
    ResultType operator()(int i, InputType input)
    {
        (void)i;
        return _value = _binary_function(std::move(_value), input);
    }

    // mutable state means this code is not referentially transparent :(
    F _binary_function;
    T _value;
};

}
