// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../../datatypes.hpp"
#include "emit.hpp"

namespace seq {

// This is a generic implementation for a stage, intended for advanced users.
// You can find a usage example in the corresponding unit test.
// The idea is that you pass a 'transformation' function into the generic stage,
// to define its behavior. This transformation function must take exactly two
// arguments: an 'emit' function and the value to be processed. The emit
// function is a wrapper around the call to '_successor.receive(value)`, which
// allows you to send 0, 1, 2, or more computation results to the following
// stages, via a corresponding number of calls to emit(value).

template <typename T, typename F, typename S>
struct Stage {
    using Input = T;

    Stage(F transformation, S successor) : _transformation{transformation}, _successor{successor}, _emit{_successor} {}

    Status receive(Input&& value) {
        return _transformation(_emit, std::forward<Input>(value));
    }

    F _transformation;
    S _successor;
    Emit<S> _emit;
};

template <typename T, typename F, typename S>
auto stage(F function, S successor) {
    return Stage<T, F, S>{function, successor};
}

}
