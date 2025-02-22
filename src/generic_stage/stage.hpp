// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../datatypes.hpp"
#include "emit.hpp"

namespace seq {

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
