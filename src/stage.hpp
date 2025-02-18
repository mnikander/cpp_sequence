// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "datatypes.hpp"
#include "emit.hpp"

namespace seq {

template <typename T, typename F, typename S>
struct Stage {
    using value_type = T;

    Stage(F transformation, S successor) : _transformation{transformation}, _successor{successor}, _emit{_successor} {}

    void receive(value_type&& value) {
        _transformation(_emit, std::forward<value_type>(value));
    }

    F _transformation;
    S _successor;
    Emit<S> _emit;
};

template <typename T, typename F, typename S>
auto make_stage(F function, S successor) {
    return Stage<T, F, S>{function, successor};
}

}
