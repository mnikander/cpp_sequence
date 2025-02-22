// Copyright (c) 2025, Marco Nikander

#pragma once
#include <cassert>
#include <utility> // forward
#include "../datatypes.hpp"
#include "../emit.hpp"
#include "concept_stage.hpp"

namespace seq {

template <typename I, typename S> requires Receiver<S>
struct ConceptIota {
    using Input = I;

    ConceptIota(I init, S successor) : _index{init}, _successor{successor}, _emit{_successor} {}
    
    I _index;
    S _successor;
    Emit<S> _emit;
};

template <typename I, typename S> requires Receiver<S>
Status yield(ConceptIota<I, S> & generator, typename ConceptIota<I, S>::Input const count = 1) {
    assert(count >= 0);
    Status status = OK;
    for(typename ConceptIota<I, S>::Input i = 0; i < count && status == OK; ++i) {
        status = receive(std::forward<typename ConceptIota<I, S>::Input>(generator._index), generator._successor);
        ++(generator._index);
    }
    return status;
}

template <typename I, typename S> requires Receiver<S>
Status run(ConceptIota<I, S> & generator) {
    Status status = OK;
    while(status == OK) {
        status = receive(std::forward<I>(generator._index), generator._successor);
        if(status == OK) {
            ++(generator._index);
        }
    }
    return status;
}

template <typename I, typename S> requires Receiver<S>
auto iotaConcept(I init, S successor) {
    return ConceptIota<I, S>{init, successor};
}

template <typename S> requires Receiver<S>
auto iotaConcept(S successor) {
    return ConceptIota<typename S::Input, S>{0, successor};
}

}
