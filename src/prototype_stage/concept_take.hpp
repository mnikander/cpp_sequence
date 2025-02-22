// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <concepts>
#include <utility> // forward
#include "../datatypes.hpp"
#include "concept_stage.hpp"

namespace seq {

template <typename I, typename S> requires Receiver<S>
struct ConceptTake {
    using Input = I;

    ConceptTake(i64 howMany, S successor) : _howMany{howMany}, _successor{successor} { assert(_howMany >= 0); }
    
    i64 const _howMany;
    i64 _counter{0};
    S _successor;
};

template <typename I, typename S> requires Receiver<S>
Status receive(I&& value, ConceptTake<I, S>& stage) {
    if (stage._counter < stage._howMany) {
        stage._counter++;
        return receive(std::forward<typename ConceptTake<I, S>::Input>(value), stage._successor);
    }
    else {
        return HALT;
    }
}

template <typename I, typename S> requires Receiver<S>
auto takeConcept(i64 howMany, S successor) {
    return ConceptTake<I, S>{howMany, successor};
}

}
