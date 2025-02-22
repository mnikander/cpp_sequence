// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include <vector>
#include "../datatypes.hpp"

namespace seq {

template <typename T>
struct VectorSink {
    using Input = T;

    VectorSink(std::vector<T>& vector) : _vector{vector} {}

    Status receive(Input&& value) {
        _vector.push_back(std::forward<Input>(value));
        return OK;
    }

    std::vector<T>& _vector;
};

template <typename T>
auto to_vector(std::vector<T>& vector) {
    return VectorSink<T>{vector};
}

}
