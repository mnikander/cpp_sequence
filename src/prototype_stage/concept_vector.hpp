// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include <vector>
#include "../datatypes.hpp"
#include "concept_stage.hpp"

namespace seq {

template <typename I>
struct ConceptVector {
    using Input = I;

    ConceptVector(std::vector<I>& vector) : _vector{vector} {}
    
    std::vector<I>& _vector;
};

template <typename I>
Status receive(I&& value, ConceptVector<I>& sink) {
    sink._vector.push_back(std::forward<I>(value));
    return OK;
}

template <typename I>
auto toVectorConcept(std::vector<I>& vector) {
    return ConceptVector<I>{vector};
}

}
