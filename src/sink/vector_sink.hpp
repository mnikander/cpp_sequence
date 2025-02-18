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

    void receive(Input&& value) {
        _vector.push_back(std::forward<Input>(value));
    }

    std::vector<T>& _vector;
};

template <typename T>
auto make_vector_sink(std::vector<T>& vector) {
    return VectorSink<T>{vector};
}

}
