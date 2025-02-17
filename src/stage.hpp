#pragma once
#include <utility> // forward
#include "basic_datatypes.hpp"
#include "emit.hpp"

namespace seq {

template <typename T, typename F, typename S>
struct Stage {
    using value_type = T;

    Stage(F transformation, S successor) : _transformation{transformation}, _successor{successor}, _emit{_successor} {}

    void receive(value_type value) {
        _transformation(_emit, value);
    }

    F _transformation;
    S _successor;
    Emit<S> _emit;
};

template <typename T, typename F, typename S>
Stage<T, F, S> make_stage(F function, S successor) {
    return Stage<T, F, S>{function, successor};
}

}
