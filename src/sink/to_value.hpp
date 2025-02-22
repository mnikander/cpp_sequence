// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {

template <typename T>
struct ValueSink {
    using Input = T;

    ValueSink(T& value) : _value{value} {}

    Status receive(Input&& value) {
        _value = std::forward<Input>(value);
        return OK;
    }

    T& _value;
};

template <typename T>
auto toValue(T& value) {
    return ValueSink<T>{value};
}

}
