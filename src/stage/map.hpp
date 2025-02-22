// Copyright (c) 2025, Marco Nikander

#pragma once
#include <utility> // forward
#include "../datatypes.hpp"

namespace seq {
namespace {

template <typename I, typename F, typename S>
struct MapImpl {
    using Input = I;

    explicit MapImpl(F unaryFunction, S successor) : _function{unaryFunction}, _successor{successor} {}

    Status receive(Input&& value) {
        return _successor.receive(_function(std::forward<Input>(value))); // apply the function and pass to the next stage
    }

    F _function;
    S _successor;
};
}

template <typename I, typename F, typename S>
auto map(F unaryFunction, S successor) {
    return MapImpl<I, F, S>{unaryFunction, successor};
}

}
