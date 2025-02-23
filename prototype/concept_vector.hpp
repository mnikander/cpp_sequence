// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include <vector>
#include "../src/datatypes.hpp"
#include "concept_stage.hpp"

namespace seq {
namespace proto {
namespace con {

template <typename I>
struct ToVectorImpl {
    using Input = I;

    ToVectorImpl(std::vector<I>& vector) : _vector{vector} {}
    
    Status receive(I&& value) {
        _vector.push_back(std::forward<I>(value));
        return OK;
    }

    std::vector<I>& _vector;
};    

template <typename I>
auto to_vector(std::vector<I>& vector) {
    return ToVectorImpl<I>{vector};
}

}
}
}
