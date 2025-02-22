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
    
    Status receive(I&& value) {
        if (_counter < _howMany) {
            _counter++;
            return _successor.receive(std::forward<typename ConceptTake<I, S>::Input>(value));
        }
        else {
            return HALT;
        }
    }

    i64 const _howMany;
    i64 _counter{0};
    S _successor;
};

template <typename I, typename S> requires Receiver<S>
auto takeConcept(i64 howMany, S successor) {
    return ConceptTake<I, S>{howMany, successor};
}

}
